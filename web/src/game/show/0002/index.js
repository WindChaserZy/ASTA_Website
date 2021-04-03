import { Button } from "antd";
import React, {Component} from "react";
import Unity, { UnityContext } from "react-unity-webgl";
import Loading from '../../../loading.js';


class GameContainer extends Component{
	state = {
		progression: 0,
	};
	constructor(props) {
		super(props);
		this.buildPath = "show/0002/Build/";
		this.unityContext = new UnityContext({
			loaderUrl: this.buildPath + "build.loader.js",
			dataUrl: this.buildPath + "build.data.unityweb",
			frameworkUrl: this.buildPath + "build.framework.js.unityweb",
			codeUrl: this.buildPath + "build.wasm.unityweb",
		});
	
		this.unityContext.on("progress", (progression) => {
		  this.setState({
			progression: progression,
		  });
		});
		this.unityContext.on("loaded", () => {
			console.log("loaded");
			var info = this.props.data["record_info"] || this.props.data["everyround_info"];
			var cmd = this.props.data["record_cmd"] || this.props.data["log_info"];
			let data = info + '~' + cmd;
			console.log(info);
			console.log(cmd);
			setTimeout(()=>{
				this.unityContext.send("GameManager", "loadData", data);
			},10);
		});
	}
	componentWillReceiveProps(nextProps){
		if (this.props.data != nextProps.data){
			window.location.reload();
		}
	}
	render(){
		if (this.props.data == null) return;
		return (
			<div>
				{this.state.progression<1&&(
					<Loading
						progression = {this.state.progression}
					/>
				)}
				<Unity
					unityContext={this.unityContext}
					width="100%"
					height="750px"
				/>
			</div>
		)
	}
}
export default GameContainer;