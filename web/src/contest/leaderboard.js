import '../config';
import { Link } from 'react-router-dom';
import $ from 'jquery';
import React, { Component } from 'react';
import Loading from '../loading.js';
import reqwest from 'reqwest';
import { Tag, Table } from 'antd';
import UserShow from '../user/show.js';


class ListElement extends Component{
	state = {
		data: [],
		pagination: {pageSize: 10},
		loading: false,
	}
	getTotalCount = (params = {}) => {
		let data = { ...params, }
		if (this.props.contestId){
			data['id'] = this.props.contestId
		}
		let url = global.constants.server + 'contest/leaderboard/count/';
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
			data['id'] = this.props.contestId
		}
		reqwest({
			url: global.constants.server + 'contest/leaderboard/',
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
		let columns = [
			{
				title: 'Rank',
				dataIndex: 'rank',
				sorter: true,
			},
			{
				title: 'Team',
				dataIndex: 'teamName',
			},
			{
				title: 'Captain',
				dataIndex: 'captain',
				render: user => <UserShow username={user.username} avatar={user.avatar}/>,
			},
			{
				title: 'Total Score',
				dataIndex: 'totalScore',
				align: 'center',
				render: score=><b>{Math.round(score*100000)/100000}</b>
			},
		  ];
		for (let i = 0; i < this.props.problems.length; i++){
			columns.push({
				title: this.props.problems[i].title,
				dataIndex: 'stdScore',
				align: 'center',
				render: (stdScore, record)=>{return <span><b>{Math.round(stdScore[i]*100000)/100000}</b>({record.score[i]})</span>},
			});
		}
		return (
			<div id = "root"  style = {{padding: this.props.padding ? this.props.padding : 60}}>
				{this.props.contestId===undefined &&
					<h1 style={{lineHeight: 4, fontSize: 20,fontWeight: 700}}>Submissions</h1>
				}
				<Table
					columns={columns}
					rowKey={record => record.rank}
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
