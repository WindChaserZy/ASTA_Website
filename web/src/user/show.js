import '../config';
import $ from 'jquery';
import { withRouter, Link } from 'react-router-dom';
import React, { Component } from 'react';
import { message, Avatar, Tooltip } from 'antd';
import './show.css'

class UserShow extends Component{
	state = {
	}
	updateUser = (userData) => {
		if (userData.avatar != null && userData.username != null){
			this.setState({user: {username: userData.username, avatar: userData.avatar}})
			return
		}
		let data = {};
		if (userData.id != null){
			data.id = userData.id;
		}
		if (userData.username != null){
			data.username = userData.username;
		}
		let url = global.constants.server + 'user/';
		$.get({
			url: url,
			data: data,
			crossDomain: true,
			xhrFields: {
				withCredentials: true
			},
			success: function (result) {
				this.setState({user: result})
			}.bind(this),
			error: function (result) {
				message.error(result.responseText)
			}.bind(this),
		});
	}
	componentWillMount(){
		this.updateUser(this.props);
	}
	componentWillReceiveProps(nextProps){
		if (this.props.username!=nextProps.username || this.props.avatar!=nextProps.avatar){
			this.updateUser(nextProps);
		}
	}
	render(){
		if (this.state.user == null){
			return (
				<span>
					<Avatar size={24} icon = "user"  />
					Loading
				</span>
			)
		}else{
			let {user} = this.state;
			if (this.props.mode && this.props.mode == 'mini'){
				return (
					<Link to={"/user/" + user.username}>
						<Tooltip title={user.username}>
							<Avatar size={24} src = {global.constants.server + user.avatar} />
						</Tooltip>
					</Link>
				)
			}else{
				return (
					<Link to={"/user/" + user.username}>
						<span>
							<Avatar size={32} src = {global.constants.server + user.avatar} />
							<span className='username'>{user.username}</span>
						</span>
					</Link>
				)
			}
		}
	}
}
export default UserShow;