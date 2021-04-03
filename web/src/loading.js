import './config';
import React, { Component } from 'react';
import { Spin  } from 'antd';
import { string } from 'prop-types';


class Loading extends Component{
	shouldComponentUpdate(){
		return true;
	}
	render(){
		let tip = "Loading...";
		if (this.props.progression){
			tip += (this.props.progression*100).toFixed(2) + "%";
		}
		return (
			<div  className = "root"  style={{display: 'flex', alignItems: 'center', justifyContent: 'center'}}>
				<Spin  tip = {tip}  size = "large"></Spin>
			</div>
		)
	}
}

export default Loading;