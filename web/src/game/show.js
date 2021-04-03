import '../config';
import { Link } from 'react-router-dom';
import $, { data } from 'jquery';
import React, { Component } from 'react';
import Loading from '../loading.js';
import { Button, List, Col, Row, message } from 'antd';
import GameContainer_0002 from './show/0002/index.js'


class GameShow extends Component{
	state = {
	}
	getData = (id = this.props.match.params.id) => {
		let url = global.constants.server + 'game/record/get/';
		this.gameListRequest = $.get({
			url: url,
            data: { id : id },
			success: function (result) {
				this.setState({data : result});
			}.bind(this),
			error: function (result) {
				message.error(result.responseText)
			}.bind(this),
		})
	}
	componentWillMount(){
		this.getData();
	}
	componentWillReceiveProps(nextProps){
		if (this.props.match.params.id != nextProps.match.params.id){
			this.getData(nextProps.match.params.id);
		}
	}
	render(){
		if (this.state.data == null){
			return (
				<Loading/>
			)
		}
        const id = this.props.match.params.id;
        const { data } = this.state;
		return (
			<div className = "root" style = {{padding: 10}}>

				{data.game==2&&(
                    <div>
                        <GameContainer_0002 data={data}/>
                    </div>
                )}
			</div>
		)
	}
}
export default GameShow;
