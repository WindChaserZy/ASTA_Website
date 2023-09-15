import '../config';
import { Link } from 'react-router-dom';
import $ from 'jquery';
import React, { Component } from 'react';
import { Comment, message, Button, Card, Modal, Tag, Tabs, List, Divider, Form, Input, Icon } from 'antd';
import { TweenOneGroup } from 'rc-tween-one';
import Loading from '../loading.js';
import UserShow from '../user/show.js';
import Editor from '../markdown/edit.js';
import './edit.css';
const { confirm } = Modal;
const { TabPane } = Tabs;
const { TextArea } = Input;


class TagEditor extends Component{
	state = {
		inputTagVisible: false,
		inputTagValue: '',
	}
	triggerChange = changedValue => {
		const { onChange, value } = this.props;
		if (onChange) {
			onChange({
				...value,
				...changedValue,
			});
		}
	};
	handleClose = removedTag => {
		const tags = this.props.value.tags.filter(tag => tag !== removedTag);
		this.triggerChange({ tags });
	};
	showInput = () => {
		this.setState({ inputTagVisible: true }, () => this.input.focus());
	};
	handleTagInputChange = e => {
		this.setState({ inputTagValue: e.target.value });
	};
	handleTagInputConfirm = () => {
		const { inputTagValue } = this.state;
		let tags = this.props.value.tags;
		if (inputTagValue && tags.indexOf(inputTagValue) === -1) {
			tags = [...tags, inputTagValue];
		}
		this.setState({
			inputTagVisible: false,
			inputTagValue: '',
		});
		this.triggerChange({ tags });
	};
	saveInputRef = input => (this.input = input);
	forMap = tag => {
		const tagElem = (
			<Tag
				closable
				onClose={e => {
					e.preventDefault();
					this.handleClose(tag);
				}}
			>
				{tag}
			</Tag>
		);
		return (
			<span key={tag} style={{ display: 'inline-block' }}>
				{tagElem}
			</span>
		);
	};
	render(){
		const tags = this.props.value.tags;
		const { inputTagValue, inputTagVisible } = this.state;
		const tagChild = tags.map(this.forMap);
		return(
			<div>
				<div>
					<TweenOneGroup
						enter={{
							scale: 0.8,
							opacity: 0,
							type: 'from',
							duration: 100,
							onComplete: e => {
								e.target.style = '';
							},
						}}
						leave={{ opacity: 0, width: 0, scale: 0, duration: 200 }}
						appear={false}
					>
						{tagChild}
						
						{inputTagVisible && (
							<Input
								ref={this.saveInputRef}
								type="text"
								size="small"
								style={{ width: 78 }}
								value={inputTagValue}
								onChange={this.handleTagInputChange}
								onBlur={this.handleTagInputConfirm}
								onPressEnter={this.handleTagInputConfirm}
							/>
						)}
						{!inputTagVisible && (
							<Tag onClick={this.showInput} style={{ background: '#fff', borderStyle: 'dashed' }}>
								<Icon type="plus" /> New Tag
							</Tag>
						)}
					</TweenOneGroup>
				</div>
				
			</div>
		)
	}
}

class Edit extends Component{
	state = {
	}
	getmaterialData(id = this.props.match.params.id){
		if (id === undefined){
			this.setState({title: '', content: '', tags: []})
		}else{
			let url = global.constants.server + 'material/';
			$.get({
				url: url,
				data: {id: id},
				crossDomain: true,
				xhrFields: {
					withCredentials: true
				},
				success: function (result) {
					this.setState({title: result.title, content: result.content, tags: result.tags})
				}.bind(this),
				error: function (result) {
					message.error(result.responseText)
				}.bind(this),
			});
		}
	}
	componentWillMount(){
		this.getmaterialData();
	}
	componentWillReceiveProps(nextProps){
		if (this.props.match.params.id != nextProps.match.params.id){
			this.getmaterialData(nextProps.match.params.id);
		}
	}
	handleChange(value) {
		this.setState({content: value});
	}
	handleSubmit = (e) => {
		e.preventDefault();
		this.props.form.validateFields((err, values) => {
			let data = values;
			data.tags = JSON.stringify(data.tags.tags);
			if (this.props.match.params.id){
				data.id = this.props.match.params.id
			}
			if (!err) {
				let url = global.constants.server + 'material/edit/';
				this.serverRequest = $.post({
					url: url,
					data: values,
					crossDomain: true,
					xhrFields: {
						withCredentials: true
					},
					success: function (result) {
						message.success(result)
						if (data.id){
							this.props.history.push('/material/' + data.id)
						}else{
							this.props.history.push('/material')
						}
					}.bind(this),
					error: function (result) {
						message.error(result.responseText)
					}.bind(this),
				});
			}
		});
	};
	render(){
		if (this.state.title == null){
			return (
				<Loading/>
			)
		}
		const { getFieldDecorator } = this.props.form;
		return (
			<div className = "root">
				<Form onSubmit={this.handleSubmit}>
					<Form.Item label='Title'>
						{getFieldDecorator('title', {
							rules: [{ required: true, message: 'Please input the title!' }],
							initialValue: this.state.title,
						})(
							<Input/>,
						)}
					</Form.Item>
					<Form.Item label='Grade'>
						{getFieldDecorator('grade', {
							rules: [{ required: true, message: 'Please input the grade!' }],
							initialValue: this.state.grade,
						})(
							<Input/>,
						)}
					</Form.Item>
					<Form.Item label='Subject'>
						{getFieldDecorator('subject', {
							rules: [{ required: true, message: 'Please input the subject!' }],
							initialValue: this.state.subject,
						})(
							<Input/>,
						)}
					</Form.Item>
					<Form.Item label='Content'>
						{getFieldDecorator('content', {
							rules: [{ required: true, message: 'Please input the content!' }],
							initialValue: this.state.content,
						})(
							<Editor/>
						)}
						
					</Form.Item>
					<Form.Item>
						{getFieldDecorator('tags', {
							initialValue: {tags: this.state.tags}
						})(
							<TagEditor/>
						)}
					</Form.Item>
					<div className='right-button'>
					<Form.Item>
						<Button type="primary" htmlType="submit">
							Publish
						</Button>
					</Form.Item>
					</div>
				</Form>
			</div>
		)
	}
}

export default Form.create({ name: 'Material_edit' })(Edit);