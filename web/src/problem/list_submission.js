import '../config';
import { Link } from 'react-router-dom';
import $ from 'jquery';
import React, { Component } from 'react';
import Loading from '../loading.js';
import reqwest from 'reqwest';
import { Tag, Table } from 'antd';
import UserShow from '../user/show.js';

const columns = [
	{
		title: 'ID',
		dataIndex: 'id',
		sorter: true,
	},
	{
		title: 'Problem',
		dataIndex: 'problem',
		render: problem => <Link to={'problem/'+problem.id}>#{problem.id} {problem.title}</Link>,
	},
	{
		title: 'User',
		dataIndex: 'user',
		render: user => <UserShow username={user}/>
	},
	{
		title: 'Status',
		dataIndex: 'status',
		render: status =>{
			let color = 'red';
			switch (status.toUpperCase()){
				case 'WAITING': color = 'cyan';break;
				case 'JUDGING': color = 'yellow';break;
				case 'ACCEPT': color = 'green';break;
			}
			return <Tag color={color} >{status}</Tag>
		}
	},
	{
		title: 'Score',
		dataIndex: 'score',
	},
	{
		title: 'Date',
		dataIndex: 'date',
	},
	{
		title: 'Time',
		dataIndex: 'time',
		align: 'center',
		render: time => parseInt(time*1000),
	},
  ];

class ListElement extends Component{
	state = {
		data: [],
		pagination: {pageSize: 6},
		loading: false,
	}
	getTotalCount = (params = {}) => {
		let data = { ...params, }
		if (this.props.contestId){
			data['contest'] = this.props.contestId
		}
		let url = global.constants.server + 'submission/count/';
		this.totalCountRequest = $.get({
			url: url,
			data: data,
			success: function (result) {
				this.setState({totalCount : result.number});
				this.fetch();
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
			url: global.constants.server + 'submission/list/',
			method: 'get',
			data: data,
			type: 'json',
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
		return (
			<div id = "root"  style = {{padding: this.props.padding ? this.props.padding : 60}}>
				{this.props.contestId===undefined &&
					<h1 style={{lineHeight: 4, fontSize: 20,fontWeight: 700}}>Submissions</h1>
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
