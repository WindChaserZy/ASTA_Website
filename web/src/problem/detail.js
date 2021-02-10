import '../config';
import { Link } from 'react-router-dom';
import $ from 'jquery';
import React, { Component } from 'react';
import { message, Button, Modal, Tabs, Divider, Input, Popconfirm, Icon, Upload } from 'antd';
import Loading from '../loading.js';
import UserShow from '../user/show.js';
import MarkdownView from '../markdown/view.js';
import MarkdownEditor from '../markdown/edit.js';
import './detail.css';
const { confirm } = Modal;
const { TabPane } = Tabs;
const { TextArea } = Input;

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
		let url = global.constants.server + 'problem/';
		$.get({
			url: url,
			crossDomain: true,
			data: {'id': id},
			xhrFields: {
				withCredentials: true
			},
			async: true,
			success: function (result) {
				this.setState({data: result})
			}.bind(this),
			error: function (result) {
				message.error(result.responseText)
			}.bind(this),
		})
	}
	componentWillMount(){
		this.getInfo()
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
		const { id, contestId } = this.props.match.params;
		let submitData = { id : id };
		if (contestId) submitData['contest'] = contestId;
		return (
			<div className = "root">
				<div className='title'> {this.state.data.title} </div>
				<div className='info'>
					<UserShow username={this.state.data.author}/>
					<span className='time'>{this.state.data.time}</span>
					&nbsp;
					<Upload
						action={global.constants.server + 'problem/submit/'}
						accept='.zip,.cpp'
						name='code'
						onChange={(info)=>{
							if (info.file.status === 'done') {
								console.log(info.file.response);
								message.success(info.file.response.message);
								if (contestId && info.file.response.inContest){
									this.props.history.push(`/contest/${contestId}/submission`)
								}else{
									this.props.history.push('/submission')
								}
							} else if (info.file.status === 'error') {
								if (info.file.response){
									message.error(info.file.response);
								}else{
									message.error('Submitted failed');
								}
							}
						}}
						data={submitData}
						withCredentials={true}
						showUploadList={false}
					>
						<Button>
							<Icon type="upload" /> Submit
						</Button>
					</Upload>
				</div>
				<Divider />
				
				
				<MarkdownView
					source={this.state.data.content}
				/>
			</div>
		)
	}
}

export default Detail;