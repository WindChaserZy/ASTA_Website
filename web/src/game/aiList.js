import '../config';
import $ from 'jquery';
import React, { Component } from 'react';
import { Link } from 'react-router-dom';
import { Tabs, Form, Icon, Input, Button, Card, Modal, Empty, message, Table, Divider, Result } from 'antd';
import Loading from '../loading.js';
import AiDetail from './aiDetail.js'
import UserShow from '../user/show.js';
const { confirm } = Modal;
const { TextArea } = Input;
const { Column } = Table;
const { TabPane } = Tabs;
const { Meta } = Card;


class Bot extends Component{
	state = {
		aiSelect: null,
		keyTab: 'list',
	}
	
	getGameInfo = (username=this.props.user.username, game=this.props.game, team=null) => {
		let url = global.constants.server + 'game/ai/list/';
		let data = {'game': game};
		if (team){
			data.team = team;
		}else{
			data.username = username;
		}
		$.get({
			url: url,
			crossDomain: true,
			data: data,
			xhrFields: {
				withCredentials: true,
			},
			async: true,
			success: function (result) {
				var aiSelect = this.state.aiSelect;
				if (result.length == 0){
					aiSelect = null;
					this.state.keyTab = 'ai';
				}else if (this.state.ai==null || this.state.ai.length==0){
					aiSelect = result[0].id;
				}else if (result.length > this.state.ai.length){
					aiSelect = result[result.length-1].id;
                }else if (result.length > this.state.ai.length){
					aiSelect = result[0].id;
				}
				this.setState({ai: result, aiSelect});
			}.bind(this),
			error: function (result) {
				message.error(result.responseText);
			}.bind(this),
		})
	}
	getTeamInfo = (username=this.props.user.username, contestid=this.props.contest, game=this.props.game) => {
		let url = global.constants.server + 'team/';
		$.get({
			url: url,
			crossDomain: true,
			data: {'username': username, 'contest': contestid},
			xhrFields: {
				withCredentials: true
			},
			async: true,
			success: function (result) {
				this.setState({team: result});
				this.getGameInfo(username, game, result.id);
			}.bind(this),
			error: function (result) {
				//message.error(result.responseText)
				this.setState({team: null})
			}.bind(this),
		})
	}
	getInfo = (username=this.props.user.username, contest=this.props.contest, game=this.props.game) => {
		if (contest){
			this.getTeamInfo(username, contest, game);
		}else{
			this.getGameInfo(username, game);
		}
	}
	componentWillMount(){
		if (this.props.game && this.props.user){
			this.getInfo();
		}
	}
	componentWillReceiveProps(nextProps){
		if (nextProps.game && nextProps.user && (this.props.game!=nextProps.game || this.props.user!=nextProps.user || this.props.contest!=nextProps.contest)){
			this.getInfo(nextProps.user.username, nextProps.contest, nextProps.game);
		}
	}
	render(){
		if (this.props.user == null){
			return (
				<div>
					<Result
						title={
							<div>
								Please <Link to='/login'>login</Link> first.
							</div>
						}
					/>
				</div>
			)
		}
		if (this.state.team === null){
			return (
				<Result
					title="You're not in a team now."
					extra={
						<div>
							<Link to={"/contest/"+this.props.contest+"/admin"}>
								Create or join a team in contest page.
							</Link>
						</div>
					}
				/>
			)
		}
		if (this.state.ai === undefined){
			return (
				<Loading />
			)
		}
		return (
			<div className = "root" style = {{padding: this.props.padding!==undefined ? this.props.padding : 60}}>
				<div style = {{marginLeft: 10, marginRight: 10, display: 'flex', flexDirection: 'row', justifyContent: 'center', alignItems: 'flex-start'}}>
					<div style={{flex: 1, margin: 10, display: 'flex', flexDirection: 'column', alignItems: 'flex-end'}}>
						{this.state.ai.map(ai =>(
							<Card hoverable
								key={ai.id}
								actions={[
									<div onClick={() => this.setState({aiSelect: ai.id, keyTab: 'add'})}>
										<Icon type="plus" key="add" />
									</div>,
									<div onClick={() => this.setState({aiSelect: ai.id, keyTab: 'ai'})}>
										<Icon type="edit" key="edit"/>,
									</div>
								]}
								style={{width: 300, borderRadius: 10, backgroundColor: (ai.id==this.state.aiSelect?'#EEE':'#FFF')}}
							>
								<div
									onClick={() => this.setState({aiSelect: ai.id, keyTab: 'list'})}
									style={{display: 'flex', flexDirection: 'row', justifyContent: 'center', alignItems: 'center'}}
								>
									<Meta
										title={(<b>{ai.name}</b>)}
										description={ai.introduction}
										style={{width: '65%'}}
									/>
									<div style={{width: '35%'}}>
										{ai.score!==undefined&&(
											<div>
												<Icon type="star" theme="filled"/>{ai.score.toFixed(3)}
											</div>
										)}
									</div>
								</div>
							</Card>
						))}
						<Card
							hoverable
							align="center"
							bodyStyle={{padding: 10, fontSize: 16}}
							style={{border: '1px dashed black', width: 150, borderRadius: 10}}
							onClick={() => this.setState({aiSelect: null, keyTab: 'ai'})}
						>
							<b>Add AI</b>
						</Card>
					</div>
					<div style={{flex: 4, margin: 10}}>
						<AiDetail
							keyTab={this.state.keyTab}
							tabChange={keyTab => this.setState({keyTab})}
							getInfo={this.getInfo}
							id={this.state.aiSelect}
							game={this.props.game}
							padding={0}
						/>
					</div>
				</div>
			</div>
		)
	}
}

export default Bot;