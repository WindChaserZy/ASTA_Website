import '../config';
import { Link } from 'react-router-dom';
import $ from 'jquery';
import React, { Component } from 'react';
//import './detail.css';
import { message, Button, Card, Modal, Tag, Tabs, List} from 'antd';
import Loading from '../loading.js'
import GameAI from './aiList.js';
import GameRecordList from './list_record.js'
import GameLeaderboard from './leaderboard.js';
import GameBotList from './botList.js'
import MarkdownView from '../markdown/view.js'
const { confirm } = Modal;
const { TabPane } = Tabs;

class Detail extends Component{
	state = {
	}
	changeTabKey = (key) => {
		const { id } = this.props.match.params;
		this.props.history.push('/game/' + id + '/' + key);
	}
	getInfo = (id = this.props.match.params.id) => {
		let url = global.constants.server + 'game/'
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
		this.getInfo();
	}
	componentWillReceiveProps(nextProps){
		if (this.props.match.params.id != nextProps.match.params.id){
			this.getInfo(nextProps.match.params.id);
		}
	}
	tabChage = (key) => {
		this.changeTabKey(key)
	}
	render(){
		if (this.state.data == null){
			return (
				<Loading/>
			)
		}
		const { user } = this.props;
		const { id, tab } = this.props.match.params;
		const { data } = this.state;
		let key = 'home';
		if (tab) key = tab;
		return (
			<div className = "root">
				<div className='title' style={{fontSize: 30, margin: 0}}> {data.name} </div>
				<Tabs activeKey={key} onTabClick={this.tabChage} type="card">
					<TabPane tab="Home" key="home">
						<div style={{marginLeft: 10}}>
							<MarkdownView
								source={data.detail}
							/>
						</div>
					</TabPane>
					<TabPane tab="leaderboard" key="leaderboard">
						<GameLeaderboard
							contest={data.contest}
							game={id}
							source={data.detail}
							padding={0}
						/>
					</TabPane>
					<TabPane tab="Record" key="record">
						<GameRecordList
							user={this.props.user}
							contest={data.contest}
							game={id}
							padding={0}
						/>
					</TabPane>
					<TabPane tab="All Bot" key="allBot">
						<GameBotList
							user={this.props.user}
							contest={data.contest}
							game={id}
							padding={0}
						/>
					</TabPane>
					<TabPane tab="My Bot" key="bot">
						<GameAI
							user={this.props.user}
							contest={data.contest}
							game={id}
							padding={0}
						/>
					</TabPane>
				</Tabs>
			</div>
		)
	}
}

export default Detail;