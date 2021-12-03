import '../config';
import $ from 'jquery';
import { Link } from 'react-router-dom';
import React, { Component } from 'react';
import Loading from '../loading.js';
import MarkdownView from '../markdown/view.js';
import { Upload, Button, message, Descriptions, Icon, Form, Input, Card, Result } from 'antd';

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
class Informathion extends Component {
	state = {
		avatarUploading: false,
		uploadLoading: false,
		avatarUrl: null
	}
    getInfo = (username = this.props.match.params.username) => {
        let url = global.constants.server + 'user/';
        $.get({
            url: url,
            crossDomain: true,
            data: {'username': username},
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
        this.getInfo();
    }
	render() {
		if (this.state.data == null){
			return (
				<Loading/>
			)
		}
		const user = this.state.data;
        console.log(user);
		return (
			<div className="root" style={{ alignItems: 'center', justifyContent: 'center', display: 'flex', flexDirection: 'column' }}>
				<div
					name="avatar"
					listType="picture-card"
					className="avatar"
				>
					<img alt="avatar" src={global.constants.server + (this.state.avatarUrl ? this.state.avatarUrl : user.avatar)} className="avatar" />
				</div>

				<Card style={{ width: '50%' }}>
                    <Descriptions title="User Info" bordered>
                        <Descriptions.Item label="昵称">{user.username}</Descriptions.Item>
                        <Descriptions.Item label="邮箱">{user.email}</Descriptions.Item>
                        <Descriptions.Item label="姓名">{user.name}</Descriptions.Item>
                        <Descriptions.Item label="班级">{user.className}</Descriptions.Item>
                        <Descriptions.Item label="自我介绍">
                            <MarkdownView
                                source={user.introduction}
                            />
                        </Descriptions.Item>
                    </Descriptions>
				</Card>
			</div>
		)
	}
}

export default Form.create({ name: 'modify' })(Informathion);
