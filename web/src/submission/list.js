import '../config';
import { getColorFromStatus } from '../config.js';
import { Link } from 'react-router-dom';
import $ from 'jquery';
import React, { Component } from 'react';
import Loading from '../loading.js';
import reqwest from 'reqwest';
import { Tag, Table, Icon } from 'antd';
import UserShow from '../user/show.js';



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
		let url = global.constants.server + 'submission/count/';
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
			url: global.constants.server + 'submission/list/',
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
				title: (
					<span>
						Status&nbsp;&nbsp;<Icon type="sync" style={{fontSize: 10}} onClick={()=>this.handleTableChange(this.state.pagination, {}, {})}/>
					</span>
				),
				dataIndex: 'status',
				render: (status, record) =>{
					return (
						<Link to={'/submission/'+record['id']}>
							<Tag color={getColorFromStatus(status)} style={{cursor: 'pointer'}}>
								{status}
							</Tag>
						</Link>
					)
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
		if (this.state.totalCount == null){
			return (
				<Loading/>
			)
		}
		return (
			<div className = "root"  style = {{padding: this.props.padding!==undefined ? this.props.padding : 60}}>
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
