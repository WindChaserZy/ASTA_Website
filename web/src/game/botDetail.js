import '../config';
import $ from 'jquery';
import React, { Component } from 'react';
import { Link } from 'react-router-dom';
import { Tabs, Form, Icon, Input, Button, Card, Modal, Upload, message, Table, Divider, Tooltip } from 'antd';
import Loading from '../loading.js';
import UserShow from '../user/show.js';
const { confirm } = Modal;
const { TextArea } = Input;
const { Column } = Table;
const { TabPane } = Tabs;

const formItemLayout = {
	labelCol: {
		xs: { span: 4 },
		sm: { span: 4 },
	},
	wrapperCol: {
		xs: { span: 20 },
		sm: { span: 20 },
	},
};
const tailFormItemLayout = {
	wrapperCol: {
		xs: {
			span: 24,
			offset: 0,
		},
		sm: {
			span: 24,
			offset: 0,
		},
	},
};


class AiUpdate extends Component{
	state={
		filename: '',
	}
	handleSubmit = (e) => {
		e.preventDefault();
		this.props.form.validateFields((err, values) => {
			if (!err) {
				this.props.handleSubmit(values);
			}
		});
	}
	render(){
		const { id } = this.props.ai;
		const { getFieldDecorator } = this.props.form;
		return (
			<div>
				<h2 align='center'> Upload a new version </h2>
				<Form {...formItemLayout} onSubmit={this.handleSubmit} className="form">
					<div style = {{display: 'flex', flexDirection: 'row', justifyContent: 'center', alignItems: 'center'}}>
						<div style={{flex: 5}}>
							<Form.Item label='Addition'>
								{getFieldDecorator('addition', {
								})(
									<Input
										placeholder="e.g. Fixed the bug ... Change the weight of ..."
									/>,
								)}
							</Form.Item>
							<Form.Item label='Code'>
								{getFieldDecorator('code', {
									rules: [{ required: true, message: 'Please select your code!' }],
									valuePropName: 'file',
								})(
									<Upload
										beforeUpload={file => {
											this.setState({filename: file.name});
											this.props.form.setFieldsValue({code: file});
											return false;
										}}
										showUploadList={false}
									>
										<Button>
											<Icon type="upload" /> Click to upload
										</Button>
										{this.state.filename}
									</Upload>,
								)}
							</Form.Item>
						</div>
						<div style={{flex: 2, display: 'flex', flexDirection: 'row', justifyContent: 'center', alignItems: 'center'}}>
							<Form.Item style = {{ textAlign : 'center', width: 150}}>
								<Button type="primary" htmlType="submit" style={{width: 150}}>
									Update
								</Button>
							</Form.Item>
						</div>
					</div>
				</Form>
			</div>
		)
	}
}


class AiInfor extends Component{
	handleSubmit = (e) => {
		e.preventDefault();
		this.props.form.validateFields((err, values) => {
			if (!err) {
				this.props.handleSubmit(values);
			}
		});
	}
	render(){
		const { id } = this.props.ai;
		const { getFieldDecorator } = this.props.form;
		return (
			<div>
				<h2 align='center'> {id===undefined?'Create a new AI':'Modify Information'} </h2>
				<Form {...formItemLayout} onSubmit={this.handleSubmit} className="form">
					<div style = {{display: 'flex', flexDirection: 'row', justifyContent: 'center', alignItems: 'center'}}>
						<div style={{flex: 5}}>
							<Form.Item label='Name'>
								{getFieldDecorator('name', {
									initialValue: this.props.ai.name,
									rules: [{ required: true, message: 'Please input the name of your bot!' }],
								})(
									<Input
										placeholder="e.g. A Strong AI"
									/>,
								)}
							</Form.Item>
							<Form.Item label='Introduction'>
								{getFieldDecorator('introduction', {
									initialValue: this.props.ai.introduction,
								})(
									<Input
										placeholder="e.g. This is a strong AI with algorithm XXX."
									/>,
								)}
							</Form.Item>
						</div>
						<div style={{flex: 2, display: 'flex', flexDirection: 'row', justifyContent: 'center', alignItems: 'center'}}>
							<Form.Item style = {{ textAlign : 'center', width: 150}}>
								<Button type="primary" htmlType="submit" style={{width: 150}}>
									{id===undefined?'Create':'Modify'}
								</Button>
							</Form.Item>
						</div>
					</div>
				</Form>
			</div>
		)
	}
}


class Bot extends Component{
	state = {
		ai: {},
	}
	loading = false
	getInfo = (id = this.props.id) => {
		if (id == null){
			return;
		}
		this.loading = true;
		let url = global.constants.server + 'game/ai/';
		$.get({
			url: url,
			crossDomain: true,
			data: {'id': id},
			xhrFields: {
				withCredentials: true
			},
			async: true,
			success: function (result) {
				this.loading = false;
				result.bot = result.bot.reverse();
				this.setState({ai: result});
			}.bind(this),
			error: function (result) {
				this.loading = false;
				message.error(result.responseText);
			}.bind(this),
		})
	}
	botRanking = (id) => {
		let url = global.constants.server + 'game/bot/ranking/';
		$.post({
			url: url,
			crossDomain: true,
			data: {'id': id},
			xhrFields: {
				withCredentials: true
			},
			async: true,
			success: function (result) {
				message.success(result);
				this.getInfo();
				this.props.getInfo();
			}.bind(this),
			error: function (result) {
				message.error(result.responseText);
			}.bind(this),
		})
	}
	downloadCode = (id) => {
		let url = global.constants.server + 'game/bot/code/';
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
	handleBotSubmit = (values) => {
		if (this.props.id === null){
			return;
		}
		const formData = new FormData();
		formData.set('code', values.code.fileList[0].originFileObj);
		if (values.addition){
			formData.set('addition', values.addition);
		}
		formData.set('id', this.props.id);
		let url = global.constants.server + 'game/ai/addbot/';
		this.serverRequest = $.post({
			url: url,
			data: formData,
			crossDomain: true,
			xhrFields: {
				withCredentials: true
			},
			processData: false,
			contentType: false,
			success: function (result) {
				message.success(result);
				this.props.tabChange('list');
				this.getInfo();
			}.bind(this),
			error: function (result) {
				message.error(result.responseText);
			}.bind(this),
		})
	}
	handleAiSubmit = (values) => {
		values.game = this.props.game;
		if (this.props.id !== null){
			values.id = this.props.id;
		}
		let url = global.constants.server + 'game/ai/modify/';
		this.serverRequest = $.post({
			url: url,
			data: values,
			crossDomain: true,
			xhrFields: {
				withCredentials: true
			},
			success: function (result) {
				message.success(result);
				this.getInfo();
				if (this.props.id == null){
					this.props.tabChange('add');
				}
				this.props.getInfo();
			}.bind(this),
			error: function (result) {
				message.error(result.responseText);
			}.bind(this),
		})
	}
	componentWillMount(){
		if (this.props.keyTab){
			this.setState({key: this.props.keyTab});
		}
		if (this.props.id){
			this.getInfo(this.props.id);
		}
	}
	componentWillReceiveProps(nextProps){
		if (this.props.id!=nextProps.id){
			if (nextProps.id){
				this.getInfo(nextProps.id);
			}else{
				this.setState({ai:{}});
			}
		}
		if (nextProps.keyTab!=this.state.keyTab){
			this.setState({key: nextProps.keyTab})
		}
	}
	shouldComponentUpdate(newProps, newState) {
		if (this.loading) return false;
		return true;
	}
	render(){
		const { id } = this.props;
		//const { getFieldDecorator } = this.props.form;
		const AiInforInner = Form.create({ name: 'ai_infor', })(AiInfor);
		const AiUpdateInner = Form.create({ name: 'ai_update', })(AiUpdate);
		var tabList;
		if (id === null){
			tabList = [
				{
					key: 'ai',
					tab: 'Create AI',
				}
			]
		}else{
			tabList = [
				{
					key: 'list',
					tab: 'Bot List',
				},
				{
					key: 'add',
					tab: 'Add Bot',
				},
				{
					key: 'ai',
					tab: 'Update AI',
				},
			]
		}
		return (
			<div className = "root" style = {{padding: this.props.padding!==undefined ? this.props.padding : 60}}>
				<Card
					style={{ width: '100%', borderRadius: 15}}
					bodyStyle={{padding: 15}}
					tabList={tabList}
					activeTabKey={this.state.key}
					onTabChange={key => {
						this.props.tabChange(key);
					}}
				>
					{this.state.key=='list'&&(
						<Table dataSource={this.state.ai.bot} pagination={{pageSize: 5}} rowKey='id'>
							<Column title="ID" dataIndex="id" key="id"/>
							<Column title="Addition" dataIndex="addition" key="addition" align='center'/>
							<Column title="Time" dataIndex="date" key="time" width={200} align='center'/>
							<Column
								title={(
									<span>
										Compile&nbsp;&nbsp;<Icon type="sync" style={{fontSize: 10}} onClick={()=>this.getInfo()}/>
									</span>
								)}
								dataIndex="compileStatus"
								key="compile"
								width={150}
								align='center'
								render={(text)=>{
									switch (text){
										case 0: return <span style={{color: 'gray'}}>Waiting</span>
										case 1: return <span style={{color: 'orange'}}>Compiling</span>
										case 2: return <span style={{color: 'red'}}>Failed</span>
										case 3: return <span style={{color: 'green'}}>Successful</span>
									}
								}}
							/>
							<Column
								title="Action"
								key="action"
								width={300}
								align='center'
								render={(test, record)=>(
									<span>
										<Button onClick={()=>this.downloadCode(record.id)}>
											<Icon type="download" /> Code
										</Button>
										{record.ranking?(
											<Tooltip title="Remove your bot from leaderboard. It will clear your score.">
												<Button onClick={()=>this.botRanking(record.id)} type="danger">
													<Icon type="star" theme="filled" /> Remove
												</Button>
											</Tooltip>
										):(
											<Tooltip title={
												record.compileStatus==3?(
													<span>
														Add your bot into leaderboard and compete width other bots.
														<br/>
														<b>It will reset your score.</b>
													</span>
												):(
													<span>
														Only available when <b>compiled sucessfully</b>.
													</span>
												)
											}>
												<Button onClick={()=>this.botRanking(record.id)} disabled={record.compileStatus<3}>
													<Icon type="star" /> Ranking
												</Button>
											</Tooltip>
										)}
									</span>
								)}
							/>
						</Table>
					)}
					{this.state.key=='add'&&(
						<AiUpdateInner
							ai = { this.state.ai }
							handleSubmit = {this.handleBotSubmit}
						/>
					)}
					{this.state.key=='ai'&&(
						<AiInforInner
							ai = { this.state.ai }
							handleSubmit = {this.handleAiSubmit}
						/>
					)}
				</Card>
			</div>
		)
	}
}

export default Bot;