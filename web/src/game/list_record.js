import '../config';
import { getColorFromStatus } from '../config.js';
import { Link } from 'react-router-dom';
import $ from 'jquery';
import React, { Component } from 'react';
import Loading from '../loading.js';
import reqwest from 'reqwest';
import { Tag, Table, Icon, Card, message, Avatar, Radio, Button, Tooltip } from 'antd';
import UserShow from '../user/show.js';
const { Meta } = Card;
const ButtonGroup = Button.Group;


class ListElement extends Component{
	state = {
		data: [],
		pagination: {pageSize: 6, current: 1},
		loading: false,
	}
	
	getTotalCount = (params = {}, game = this.props.game) => {
		let data = { ...params, }
		if (game){
			data['game'] = game;
		}
		let url = global.constants.server + 'game/record/count/';
		this.totalCountRequest = $.get({
			url: url,
			data: data,
			success: function (result) {
				this.setState({totalCount : result.number});
				
				this.fetch(
					{
						pageSize: this.state.pagination.pageSize,
						page: 1,
					},
					game,
				);
			}.bind(this)
		})
	}
	downloadRecord = (id) => {
		let url = global.constants.server + 'game/record/download/';
		$.get({
			url: url,
			crossDomain: true,
			data: {'id': id},
			xhrFields: {
				withCredentials: true
			},
			async: true,
			success: function (result) {
				window.location.href = url+'?id='+id;
			}.bind(this),
			error: function (result) {
				message.error(result.responseText);
			}.bind(this),
		})
	}
	componentWillMount(){
		this.getTotalCount();
	}
	handleTableChange = (pagination, filters, sorter) => {
		const pager = { ...this.state.pagination };
		pager.current = pagination.current;
		this.setState({
			pagination: pager,
		});
		this.fetch({
			pageSize: pagination.pageSize,
			page: pagination.current,
			sortField: sorter.field,
			sortOrder: sorter.order,
			...filters,
		});
	};
	
	fetch = (params = {}, game = this.props.game) => {
		this.setState({ loading: true });
		let data = { ...params, }
		if (game){
			data['game'] = game;
		}
		reqwest({
			url: global.constants.server + 'game/record/list/',
			method: 'get',
			data: data,
			type: 'json',
			crossOrigin: true,
			withCredentials: true,
		}).then(data => {
			const pagination = { ...this.state.pagination };
			// Read total count from server
			// pagination.total = data.totalCount;
			pagination.total = this.state.totalCount;
			this.setState({
				loading: false,
				data: data,
				pagination,
			});
		});
	};
	componentWillReceiveProps(nextProps){
		if (this.props.game != nextProps.game){
			this.getTotalCount({}, nextProps.game);
		}
	}
	render(){
		const columns = [
			{
				title: 'ID',
				dataIndex: 'id',
				align: 'center',
			},
			{
				title: 'Game',
				dataIndex: 'game',
				width: 100,
				align: 'center',
				render: game => <Link to={'/game/'+game.id}>{game.name}</Link>,
			},
			{
				title: (
					<span>
						Status&nbsp;&nbsp;<Icon type="sync" style={{fontSize: 10}} onClick={()=>this.handleTableChange(this.state.pagination, {}, {})}/>
					</span>
				),
				dataIndex: 'status',
				align: 'center',
				width: 130,
				render: (status, record) =>{
					return (
						<Tag color={getColorFromStatus(status)}>
							{status}
						</Tag>
					)
				}
			},
			{
				title: 'Score',
				dataIndex: 'bot',
				align: 'center',
				width: 800,
				render: (bot, record) => {
					return (
						<div style={{display: 'flex', flexDirection: 'row', justifyContent: 'center', alignItems: 'center', flexWrap: 'wrap'}}>
							{bot.map(botPlay=>{
								let color = 'gray', icon = 'minus';
								if (botPlay.deltaRankingScore > 0){
									color = 'red';
									icon = 'caret-up';
								}else if (botPlay.deltaRankingScore < 0){
									color = 'green';
									icon = 'caret-down';
								}
								return  (
									<Card style={{width: 260, height: 90, display: 'block-inline', margin: 5}} bodyStyle={{padding: 15}}>
										<div style={{display: 'flex', flexDirection: 'row', justifyContent: 'center', alignItems: 'center'}}>
											<Meta
												avatar={botPlay.ai.team?(
													<div style={{display: 'flex', flexDirection: 'column', justifyContent: 'center', alignItems: 'center'}}>
														<Avatar src={global.constants.server + botPlay.ai.captain.avatar} size={30} />
														<div>
															<div style={{width: 70, fontSize: 13}}>
																{botPlay.ai.team.name}
															</div>
														</div>
													</div>
												):(
													<div style={{display: 'flex', flexDirection: 'column', justifyContent: 'center', alignItems: 'center'}}>
														<Avatar src={global.constants.server + botPlay.ai.user.avatar}/>
														<div>
															{botPlay.ai.user.username}
														</div>
													</div>
												)}
												style={{padding: 5, width: 180}}
												title={(<Tooltip title={"bot ID : "+botPlay.id}>{botPlay.ai.name}</Tooltip>)}
												description={botPlay.oldRankingScore.toFixed(3)}
											/>
											<div style={{width: 80}} align='center'>
												{record.ranking&&(
													<div style={{color: color}}>
														<Icon type={icon} />{botPlay.deltaRankingScore.toFixed(3)}
													</div>
												)}
												<b>{botPlay.originalScore.toFixed(3)}</b>
											</div>
										</div>
									</Card>
								)
							})}
						</div>
					)
						
				}
			},
			{
				title: 'Action',
				key: 'action',
				align: 'center',
				width: 150,
				render:(action, record)=>(
					<div>
						<Link to={"/gameShow/"+record.id}>
							<Button icon="play-square" style={{marginRight: 5}} size="large"/>
						</Link>
						<Button onClick={()=>this.downloadRecord(record.id)} icon="download" style={{margin: 0}} size="large"/>
					</div>
				)
			},
			{
				title: 'Date',
				dataIndex: 'date',
				align: 'center',
			},
			{
				title: 'Time',
				dataIndex: 'time',
				align: 'center',
				render: time => parseInt(time*1000),
			},
		  ];
		if (this.state.totalCount == null){
			return (
				<Loading/>
			)
		}
		return (
			<div className = "root"  style = {{padding: this.props.padding!==undefined ? this.props.padding : 60}}>
				{this.props.game===undefined &&
					<h1 style={{lineHeight: 4, fontSize: 20,fontWeight: 700}}>Record</h1>
				}
				<Table
					columns={columns}
					rowKey={record => record.id}
					dataSource={this.state.data}
					pagination={this.state.pagination}
					loading={this.state.loading}
					onChange={this.handleTableChange}
				/>
			</div>
		)
	}
}
export default ListElement;
