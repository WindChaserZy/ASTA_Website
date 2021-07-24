import '../config';
import { Link } from 'react-router-dom';
import $ from 'jquery';
import React, { Component } from 'react';
import Loading from '../loading.js';
import reqwest from 'reqwest';
import { Icon, Table, Tooltip } from 'antd';
import UserShow from '../user/show.js';


class ListElement extends Component{
	state = {
		data: [],
		pagination: {pageSize: 10, current: 1},
		loading: false,
	}
	getTotalCount = (params = {}) => {
		let data = { ...params, }
		if (this.props.game){
			data['game'] = this.props.game
		}
		let url = global.constants.server + 'game/botList/count/';
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
			data['game'] = this.props.game
		}
		reqwest({
			url: global.constants.server + 'game/botList/',
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
				title: 'ID',
				dataIndex: 'id',
			},
			{
				title: 'AI',
				dataIndex: 'aiName',
			},
			{
				title: 'Time',
				dataIndex: 'date',
			},
		  ];
		if (this.props.contest === undefined){
			columns.splice(2, 0, {
				title: 'User',
				dataIndex: 'username',
			})
		}else{
			columns.splice(2, 0, {
				title: 'Team',
				dataIndex: 'teamName',
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
