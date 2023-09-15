import '../config';
import { Link } from 'react-router-dom';
import $ from 'jquery';
import React, { Component } from 'react';
import { Icon, Comment, message, Button, Card, Modal, Tag, Tabs, List, Divider, Form, Input, Avatar, Popconfirm } from 'antd';
import Loading from '../loading.js';
import UserShow from '../user/show.js';
import MarkdownView from '../markdown/view.js';
import MarkdownEditor from '../markdown/edit.js';
//import ThumbsUp from './thumbsup.js';
import './detail.css';
const { confirm } = Modal;
const { TabPane } = Tabs;
const { TextArea } = Input;

class Detail extends Component{
    state = {
		submitting: false,
		content: '',
	}
	//现在会导致一些报错
	//get files list for download(TODO)
	getList = (id) => {
		
		let url = global.constants.server + 'material/download/';
		$.get({
			url: url,
			crossDomain: true,
			data: {'id': id},
			xhrFields: {
				withCredentials: true
			},
			async: true,
			success: function (result) {
			//	this.setState({list : result});
			}.bind(this),
			error: function (result) {
				//message.error(result.responseText)
			}.bind(this),
		})
			//success: function (result) {
			//	window.location.href = url+'?id='+id;
			//}.bind(this),
		
	}
	handleChange = value => {
		this.setState({
			content: value,
		});
	}
    getCommentList = (id = this.props.match.params.id) => {
		$.get({
			url: global.constants.server + 'mcomment/list/',             
			data: { material: id },
			crossDomain: true,
			xhrFields: {
				withCredentials: true
			},
			success: function (result) {
				this.setState({mcomments: result})
			}.bind(this),
			error: function (result) {
				message.error(result.responseText)
			}.bind(this),
		})
	}
	getFileList = (id = this.props.match.params.id) => {//new
		$.get({
			url: global.constants.server + 'mfile/list/',             
			data: { material: id },
			crossDomain: true,
			xhrFields: {
				withCredentials: true
			},
			success: function (result) {
				this.setState({files: result})
			}.bind(this),
			error: function (result) {
				message.error(result.responseText)
			}.bind(this),
		})
	}
    handleSubmit = () => {
		if (!this.state.content) {
			return;
		}
		this.setState({
			submitting: true,
		});

		$.post({
			url: global.constants.server + 'mcomment/add/',                          
			data: { material: this.props.match.params.id, content: this.state.content },
			crossDomain: true,
			xhrFields: {
				withCredentials: true
			},
			success: function (result) {
				message.success(result)
				this.setState({content: ''})
				this.getCommentList()
			}.bind(this),
			error: function (result) {
				message.error(result.responseText)
			}.bind(this),
			complete: function (result){
				this.setState({submitting: false})
			}.bind(this),
		})
	};
    getInfo = (id = this.props.match.params.id) => {
		let url = global.constants.server + 'material/';
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
		this.getCommentList()
		this.getFileList()//new
	}
	componentWillReceiveProps(nextProps){
		if (this.props.match.params.id != nextProps.match.params.id){
			this.getInfo(nextProps.match.params.id)
			this.getCommentList(nextProps.match.params.id)
			this.getFileList(nextProps.match.params.id)//new
		}
	}
    deleteMaterial(id = this.props.match.params.id){
		let url = global.constants.server + 'material/delete/';
		$.post({
			url: url,
			crossDomain: true,
			data: {'id': id},
			xhrFields: {
				withCredentials: true
			},
			success: function (result) {
				message.success(result)
				this.props.history.push('/material')
			}.bind(this),
			error: function (result) {
				message.error(result.responseText)
			}.bind(this),
		})
	}
	downloadCode = (id) => {
		let url = global.constants.server + 'mfile/download/';
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
    render(){
        if (this.state.data == null){
			return (
				<Loading/>
			)
		}
		this.getList(this.state.data.id)

		//dowload url (TO CHECK)
		let downloadPos=global.constants.server+"material/download/?id="+this.state.data.id

		//preview url (TO CHECK)
		let previewPos=global.constants.server+"media/test.pdf"

        const { user } = this.props
		const { id } = this.props.match.params
        return(
            <div className = "root">
                <div className='title'> {this.state.data.title} </div>
                <div className='info'>
                    <UserShow username={this.state.data.author}/>
					<span className='time'>{this.state.data.time}</span>
                    {/*以下为编辑功能，暂时不需要
                    {(this.props.user && this.props.user.username==this.state.data.author)&&(
						<span style={{marginLeft: 20}}> 
							<Link to={'/materialEdit/' + id}>
								<Button type="primary" shape="circle" icon="edit"/>
							</Link>
							<Popconfirm
								placement="bottom"
								title={(
									<div>
										<p>Do you want to <b>delete</b> this material?</p>
									</div>
								)}
								onConfirm={() => this.deleteMaterial()}
								okText="Yes"
								cancelText="No"
							>
								<Button type="danger" shape="circle" icon="delete"/>
							</Popconfirm>
						</span>
					)}
                    */}
                </div>
				{/* <div className='likes'>
					<ThumbsUp />
				</div> */}
                <Divider />

                <MarkdownView
					source={this.state.data.content}
				/>

				{/*
				不能用的当页显示方法
				和X-Frame-Options有关
				<embed src={previewPos} type="application/pdf" width="100%" height="100%" />
				<object data={previewPos} type="application/pdf">
					This browser does not support PDFs. Please download the PDF to view it: <a href={previewPos}>Download PDF</a>
				</object>
				<iframe src={previewPos}></iframe>
				 */}

				{/*
				这里是将来用的显示列表
				理想情况下应该传入models.py中的Material]
				*/}

				<Divider />
				<List
					itemLayout="horizontal"
					dataSource={this.state.files}
					renderItem={item => (
						<List.Item key={item.id}>
							<List.Item.Meta
								description={<div>
									<UserShow 
										username={item.author}
										mode='mini'
									/>
									&nbsp;&nbsp;
									<strong>{item.author}</strong>
									&nbsp;&nbsp;
									{item.title}
									&nbsp;&nbsp;
									{item.time}
									&nbsp;&nbsp;
									<Button onClick={()=>this.downloadCode(item.id)}>
										<Icon type="download" /> Download
									</Button>
								</div>}
							/>
						</List.Item>
					)}
				/>
				{/* <Button type="primary"  style={{marginBottom: 20}}>
					<a href={downloadPos} target="_blank">Dowload测试</a>
				</Button>
                <Divider /> */}
				{/* <div className='tags'>
					{
						this.state.data.grade.map((item) => {
							return (
								<Tag key={item}>{item}</Tag>
							)
						})
					}
				</div> */}
                
                {this.state.mcomments &&(   //buliding
					<List
						locale={{emptyText:'No comment now.'}}
						className="comment-list"
						header={`${this.state.mcomments.length} replies`}
						itemLayout="horizontal"
						dataSource={this.state.mcomments}
						renderItem={item => (
							<li>
								<Comment
									className='comment'
									author={item.author}
									avatar={global.constants.server + item.avatar}
									content={<MarkdownView
											source={item.content}
										/>}
									datetime={item.time}
								/>
							</li>
						)}
					/>
				)}
                {user && (    //buliding
					<div>
						<Comment
							avatar={
								<Avatar
									src={global.constants.server + user.avatar}
									alt={user.username}
								/>
							}
							content={
								<Form>
									<Form.Item>
										<MarkdownEditor
											style={{height: 300}}
											onChange={this.handleChange}
											value={this.state.content}
										/>
									</Form.Item>
									<Form.Item>
										<Button htmlType="submit" loading={this.state.submitting} onClick={this.handleSubmit} type="primary">
											Add Comment
										</Button>
									</Form.Item>
								</Form>
							}
						/>
					</div>
				)}
            </div>
        )
    }
}

export default Detail;