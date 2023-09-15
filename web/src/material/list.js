import '../config';
import { Link } from 'react-router-dom';
import $ from 'jquery';
import React, { Component } from 'react';
import Loading from '../loading.js'
import { Button, Card, Col, Row, List, Input, Form, Icon, Divider, message, Tag , Pagination} from 'antd';
import UserShow from '../user/show.js';
//import ThumbsUp from './thumbsup.js';
import './list.css';


class ListElement extends Component{
    state = {
	}
	getList = (data = {}) => {
		let url = global.constants.server + 'material/list/';
		$.get({
			url: url,
			data: data,
			success: function (result) {
				this.setState({list : result});
			}.bind(this),
			error: function (result) {
				message.error(result.responseText)
			}.bind(this),
		})
	}
    componentWillMount(){
		let data = {}
		if (this.props.author){
			data['author'] = this.props.author
		}
		if (this.props.tag){
			data['tag'] = this.props.tag
		}
		this.getList(data)
	}
    handleSubmit = e => {
		e.preventDefault();
		this.props.form.validateFields((err, values) => {
			if (!err) {
				this.getList(values)
			}
		})
	}
	downloadCode = (id) => {
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
				window.location.href = url+'?id='+id;
			}.bind(this),
			error: function (result) {
				message.error(result.responseText);
			}.bind(this),
		})
	}
    render(){
        if (this.state.list == null){
			return (
				<Loading/>
			)
		}
		const { getFieldDecorator } = this.props.form;
        return(
            <div className = "root" style = {{padding: this.props.padding!==undefined ? this.props.padding : 60}}>
                <Form layout="inline" onSubmit={this.handleSubmit}>
				
					<Form.Item label='Grade'>
						{getFieldDecorator('grade', {
							initialValue: this.props.grade,
						})(
							<Input
								prefix={<Icon type="solution" style={{ color: 'rgba(0,0,0,.25)' }} />}
								placeholder="grade"
							/>,
						)}
					</Form.Item>
					<Form.Item label='Subject'>
						{getFieldDecorator('subject', {
							initialValue: this.props.subject,
						})(
							<Input
								prefix={<Icon type="solution" style={{ color: 'rgba(0,0,0,.25)' }} />}
								placeholder="subject"
							/>,
						)}
					</Form.Item>
				
					<Form.Item>
						<Button htmlType="submit" icon="search"/>
					</Form.Item>
					{/* <Form.Item>
						{this.props.user&&(
							<Link to="/materialEdit">
								<Button type="primary" icon="edit" style={{marginBottom: 20}}>
									New Material
								</Button>
							</Link>
						)}
					</Form.Item> */}
				</Form>
				<Divider />
                <List
					pagination={<Pagination defaultCurrent={1} total={10} />}
					itemLayout="horizontal"
					dataSource={this.state.list}
					renderItem={item => (
						<List.Item key={item.id}>
							<List.Item.Meta
								title={<Link to={"/material/"+item.id} className='materialTitle'>{item.title}</Link>}
								description={<div>
									<UserShow 
										username={item.author}
										mode='mini'
									/>
									&nbsp;&nbsp;
									{item.author}
									&nbsp;&nbsp;
									{item.time}
									&nbsp;&nbsp;
									{/* <ThumbsUp /> */}
									<div className='tags'>
										<Tag>{item.grade}</Tag>
										<Tag>{item.subject}</Tag>
									</div>
								</div>}
							/>
						</List.Item>
					)}
				/>
            </div>
        )
    }
}

export default Form.create({ name: 'Material_list' })(ListElement);