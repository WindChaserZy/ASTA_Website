import '../config';
import { getColorFromStatus } from '../config.js';
import { Link } from 'react-router-dom';
import $ from 'jquery';
import React, { Component } from 'react';
import { message, Button, Modal, Tag, List, Descriptions, Divider, Popconfirm, Icon, Upload } from 'antd';
import Loading from '../loading.js';
import UserShow from '../user/show.js';
import MarkdownView from '../markdown/view.js';
import MarkdownEditor from '../markdown/edit.js';
const { confirm } = Modal;

class Detail extends Component{
	state = {
		submitting: false,
		content: '',
	}
	handleChange = value => {
		this.setState({
			content: value,
		});
	}
	getInfo = (id = this.props.match.params.id) => {
		let url = global.constants.server + 'submission/';
		$.get({
			url: url,
			crossDomain: true,
			data: {'id': id},
			xhrFields: {
				withCredentials: true
			},
			async: true,
			success: function (result) {
				var pageNumber = Math.min(2, result.detail.length);
				result.detailSplit = [];
				for (var i = 0; i < pageNumber; i++)
				result.detailSplit.push([]);
				for (var i = 0; i < result.detail.length; i++){
					result.detail[i].index = i;
					result.detailSplit[i%pageNumber].push(result.detail[i]);
				}
				this.setState({data: result})
			}.bind(this),
			error: function (result) {
				message.error(result.responseText)
			}.bind(this),
		})
	}
	downloadCode = (id = this.props.match.params.id) => {
		let url = global.constants.server + 'submission/code/';
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
		this.getInfo();
	}
	componentWillReceiveProps(nextProps){
		if (this.props.match.params.id != nextProps.match.params.id){
			this.getInfo(nextProps.match.params.id);
		}
	}
	render(){
		if (this.state.data == null){
			return (
				<Loading/>
			)
		}
		const { user } = this.props;
		const { id } = this.props.match.params;
		const { data } = this.state;
		return (
			<div className = "root" style = {{padding: this.props.padding!==undefined ? this.props.padding : 60, display: 'flex', flexDirection: 'row', justifyContent: 'center', alignItems: 'flex-start'}}>
				<div style={{width: '90%'}}>
					<Descriptions title={(
						<span>
							Submission #{id} &nbsp;
							{(user && user.username==data.user) && (
								<Icon type="download" onClick={()=>this.downloadCode()}/>
							)}
						</span>
					)} bordered>
						<Descriptions.Item label="User">
							<UserShow username={data.user}/>
							{data.team&&(
								<span>&nbsp;({data.team})</span>
							)}
						</Descriptions.Item>
						<Descriptions.Item label="Problem">
							<Link to={'/problem/'+data.problem.id}>#{data.problem.id} {data.problem.title}</Link>
						</Descriptions.Item>
						<Descriptions.Item label="Date">
							{data.date}
						</Descriptions.Item>
						<Descriptions.Item label="Status">
							<Tag color={getColorFromStatus(data.status)}>
								{data.status}
							</Tag>
						</Descriptions.Item>
						<Descriptions.Item label="Score">
							{data.score}
						</Descriptions.Item>
						<Descriptions.Item label="Time">
							<b>{(data.time*1000).toFixed(0)}</b>&nbsp;ms
						</Descriptions.Item>
					</Descriptions>
					<Divider />
					<div style={{display: 'flex', flexDirection: 'row', justifyContent: 'center', alignItems: 'flex-start', width: '100%'}}>
						{data.detailSplit.map(page => {
							return (
								<List
									dataSource={page}
									style={{width: '50%'}}
									renderItem={item => {
										let accept = item.status.toUpperCase()=="ACCEPT";
										return (
											<List.Item>
												<List.Item.Meta
													title={(
														<span>
															#{item.index} <b>{item.status}</b>
															&nbsp;
															<span style={{color: accept?'green':'red'}}>
																<Icon type={accept?"check":"close"}/>
															</span>
														</span>
													)}
													description={(
														<span >
															Score: <b>{item.score}</b>
															&nbsp;&nbsp;&nbsp;&nbsp;
															Time: <b>{(item.time*1000).toFixed(0)}ms</b>
															&nbsp;&nbsp;&nbsp;&nbsp;
															Memory: <b>{(item.memory/1024/1024).toFixed(3)}MB</b>
														</span>
													)}
												/>
											</List.Item>
										)
									}}
								/>
							)
						})}
					</div>
				</div>
			</div>
		)
	}
}

export default Detail;