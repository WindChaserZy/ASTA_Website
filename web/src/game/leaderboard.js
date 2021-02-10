import '../config';
import { Link } from 'react-router-dom';
import $ from 'jquery';
import React, { Component } from 'react';
import Loading from '../loading.js';
import reqwest from 'reqwest';
import { Icon, Table } from 'antd';
import UserShow from '../user/show.js';


class ListElement extends Component{
	state = {
		data: [],
		pagination: {pageSize: 6, current: 1},
		loading: false,
	}
	getTotalCount = (params = {}) => {
		let data = { ...params, }
		if (this.props.game){
			data['id'] = this.props.game
		}
		let url = global.constants.server + 'game/leaderboard/count/';
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
		if (this.props.game){
			data['id'] = this.props.game
		}
		reqwest({
			url: global.constants.server + 'game/leaderboard/',
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
		if (this.state.totalCount == null){
			return (
				<Loading/>
			)
		}
		let columns = [
			{
				title: 'Rank',
				dataIndex: 'rank',
				sorter: true,
			},
			{
				title: 'AI',
				dataIndex: 'name',
			},
			{
				title: 'Introduction',
				dataIndex: 'introduction',
			},
			{
				title: (
					<span>
						Score&nbsp;&nbsp;<Icon type="sync" style={{fontSize: 10}} onClick={()=>this.handleTableChange(this.state.pagination, {}, {})}/>
					</span>
				),
				dataIndex: 'score',
				align: 'center',
				render: score=><b>{score.toFixed(3)}</b>
			},
		  ];
		if (this.props.contest === undefined){
			columns.splice(1, 0, {
				title: 'User',
				dataIndex: 'user',
				render: user => <UserShow username={user.username} avatar={user.avatar}/>,
			})
		}else{
			columns.splice(1, 0, {
				title: 'Team',
				dataIndex: 'teamName',
			},{
				title: 'Captain',
				dataIndex: 'captain',
				render: user => <UserShow username={user.username} avatar={user.avatar}/>,
			})
		}
		return (
			<div className = "root" style = {{padding: this.props.padding!==undefined ? this.props.padding : 60}}>
				<Table
					columns={columns}
					rowKey='teamId'
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
