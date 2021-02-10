import '../config';
import { getColorFromStatus } from '../config.js';
import { Link } from 'react-router-dom';
import $ from 'jquery';
import React, { Component } from 'react';
import Loading from '../loading.js';
import reqwest from 'reqwest';
import { Tag, Table, Icon, Card, Tooltip, Avatar } from 'antd';
import UserShow from '../user/show.js';
const { Meta } = Card;



class ListElement extends Component{
	state = {
		data: [],
		pagination: {pageSize: 6, current: 1},
		loading: false,
	}
	
	getTotalCount = (params = {}) => {
		let data = { ...params, }
		if (this.props.contestId){
			data['contest'] = this.props.contestId
		}
		let url = global.constants.server + 'game/record/count/';
		this.totalCountRequest = $.get({
			url: url,
			data: data,
			success: function (result) {
				this.setState({totalCount : result.number});
				
				this.fetch({
					pageSize: this.state.pagination.pageSize,
					page: 1,
				});
			}.bind(this)
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
	
	fetch = (params = {}) => {
		this.setState({ loading: true });
		let data = { ...params, }
		if (this.props.contestId){
			data['contest'] = this.props.contestId
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
				align: 'center',
				render: game => <Link to={'game/'+game.id}>{game.name}</Link>,
			},
			{
				title: (
					<span>
						Status&nbsp;&nbsp;<Icon type="sync" style={{fontSize: 10}} onClick={()=>this.handleTableChange(this.state.pagination, {}, {})}/>
					</span>
				),
				dataIndex: 'status',
				align: 'center',
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
									<Card style={{width: 260, display: 'block-inline', margin: 5}} bodyStyle={{padding: 15}}>
										<div style={{display: 'flex', flexDirection: 'row', justifyContent: 'center', alignItems: 'center'}}>
											<Meta
												avatar={this.props.contest?(
													<div style={{display: 'flex', flexDirection: 'column', justifyContent: 'center', alignItems: 'center'}}>
														<Avatar src={global.constants.server + botPlay.ai.captain.avatar}/>
														<div>
															{botPlay.ai.team.name}
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
												title={botPlay.ai.name}
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
