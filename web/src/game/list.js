import '../config';
import { Link } from 'react-router-dom';
import $ from 'jquery';
import React, { Component } from 'react';
import Loading from '../loading.js'
import { Button, List, Col, Row, Collapse } from 'antd';
const { Panel } = Collapse;


class ListElement extends Component{
	state = {
	}
	getList = () => {
		let url = global.constants.server + 'game/list/';
		this.gameListRequest = $.get({
			url: url,
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
			<div className = "root" style = {{padding: 60}}>
				<h1 style={{lineHeight: 4, fontSize: 20,fontWeight: 700}}>Games</h1>
				<Collapse accordion>
					{
						this.state.list.map((item, index) => {
							let title = item.name
							return (
								<Panel header={(
									<div>
										{item.name}
										&emsp;&emsp;&emsp;&emsp;
										<Link to={"/game/" + item.id + "/home"} style={{display: 'inline'}}>
											<Button>Enter</Button>
										</Link>
										<Link to={"/game/" + item.id + "/leaderboard"} style={{display: 'inline'}}>
											<Button>Leaderboard</Button>
										</Link>
										<Link to={"/game/" + item.id + "/record"} style={{display: 'inline'}}>
											<Button>Record</Button>
										</Link>
										<Link to={"/game/" + item.id + "/bot"} style={{display: 'inline'}}>
											<Button>Bot</Button>
										</Link>
									</div>
								)} key={index}>
									<p>{item.introduction}</p>
									<Link to={"/game/" + item.id + "/home"} style={{display: 'inline'}}>
										<Button>Enter</Button>
									</Link>
									<Link to={"/game/" + item.id + "/leaderboard"} style={{display: 'inline'}}>
										<Button>Leaderboard</Button>
									</Link>
									<Link to={"/game/" + item.id + "/record"} style={{display: 'inline'}}>
										<Button>Record</Button>
									</Link>
									<Link to={"/game/" + item.id + "/bot"} style={{display: 'inline'}}>
										<Button>Bot</Button>
									</Link>
								</Panel>
							)
						})
					}
				</Collapse>
			</div>
		)
	}
}
export default ListElement;
