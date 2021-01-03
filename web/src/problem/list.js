import '../config';
import { Link } from 'react-router-dom';
import $, { data } from 'jquery';
import React, { Component } from 'react';
import Loading from '../loading.js';
import { Button, Card, Col, Row, List } from 'antd';
import UserShow from '../user/show.js';


class ListElement extends Component{
	state = {
	}
	getList = () => {
		let url = global.constants.server + 'problem/list/';
		let data = {}
		if (this.props.contestId){
			data['contest'] = this.props.contestId
		}
		this.listRequest = $.get({
			url: url,
			data: data,
			success: function (result) {
				this.setState({list : result});
			}.bind(this)
		})
	}
	componentWillMount(){
		this.getList();
	}
	render(){
		if (this.state.list == null){
			return (
				<Loading/>
			)
		}
		return (
			<div id = "root"  style = {{padding: this.props.padding ? this.props.padding : 60}}>
				{this.props.contestId===undefined &&
					<h1 style={{lineHeight: 4, fontSize: 20,fontWeight: 700}}>Problems</h1>
				}
				<List
					itemLayout="horizontal"
					dataSource={this.state.list}
					renderItem={item => (
						<List.Item>
							<Link to={"problem/"+item.id}>
								<h1>
									{item.title}
								</h1>
							</Link>
							
							<UserShow 
								username={item.author}
								mode='mini'
							/>
							&nbsp;&nbsp;
							{item.time}
						</List.Item>
					)}
				/>
			</div>
		)
	}
}
export default ListElement;
