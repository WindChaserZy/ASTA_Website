import './config';
import React from 'react';
import { HashRouter as Router, Link, Route, Redirect } from 'react-router-dom';
import ReactDOM from 'react-dom';
import 'antd/dist/antd.css';
import './index.css';
import 'github-markdown-css/github-markdown.css';
import $ from 'jquery';
import { Layout, Menu, Typography, Icon, Button } from 'antd';
import Home from './home.js';
import Login from './user/login.js';
import Register from './user/register.js';
import ResetPassword from './user/resetPassword.js';
import Information from './user/information.js';
import UserDetail from './user/detail.js';
import ContestList from './contest/list.js';
import ContestDetail from './contest/detail.js';
import BlogList from './blog/list.js';
import BlogDetail from './blog/detail.js';
import BlogEditor from './blog/edit.js';
import TeamList from './team/list.js';
import TeamAdmin from './team/admin.js';
import ReservationList from './reservation/list.js';
import ReservationDetail from './reservation/detail.js';
import ProblemList from './problem/list.js';
import ProblemDetail from './problem/detail.js';
import SubmissionList from './submission/list.js';
import SubmissionDetail from './submission/detail.js';
import GameList from './game/list.js';
import GameDetail from './game/detail.js';
import GameShow from './game/show.js';
import ASTA_logo from './assets/logo_1.jpg';
import record_logo from './assets/record.png';

const { Header, Content, Footer, Sider } = Layout;
const { SubMenu } = Menu;
const { Title } = Typography;
const Title_word = "自动化系学生科协"
const Tips_word = ""


class App extends React.Component {
	state = {
		collapsed: false,
		user: null,
		userLoading: false,
	}
	
	onCollapse = collapsed => {
		this.setState({ collapsed });
	}
	
	componentDidMount(){
		this.updateUser();
	}
	
	download = (url) => {
		let a = document.createElement('a');
		a.href = url;
		a.click();
	};
	updateUser = (data = null) => {
		if (data != null){
			this.setState({user: data})
			return
		}
		if (this.state.userLoading) return;
		let url = global.constants.server + 'user/';
		this.loginRequest = $.get({
			url: url,
			crossDomain: true,
			xhrFields: {
				withCredentials: true
			},
			async: true,
			success: function (result) {
				if (result.id !== undefined && result !== this.state.user){
					this.setState({user: result});
				}
			}.bind(this),
			beforeSend: function(){
				this.setState({userLoading: true})
			}.bind(this),
			complete: function(){
				this.setState({userLoading: false})
			}.bind(this),
		});
	}
	
	logout = (e) => {
		let url = global.constants.server + 'logout/';
		this.logoutRequest = $.get({
			url: url,
			crossDomain: true,
			xhrFields: {
				withCredentials: true
			},
			success: function (result) {
				this.setState({user : null});
			}.bind(this)
		});
	}
	
	getUserMenu = () =>{
		if (this.state.user != null){
			return (
			<SubMenu
				key="user"
				title={
					<span>
						<Icon type="user" />
						<span>{this.state.user.username}</span>
					</span>
				}
			>
				<Menu.Item key="information" >
					<Link to="/information">
						<span>Information</span>
					</Link>
				</Menu.Item>
				<Menu.Item key="user" >
					<Link to={"/user/" + this.state.user.username}>
						<span>User</span>
					</Link>
				</Menu.Item>
				<Menu.Item key="logout" onClick={this.logout}>Log out</Menu.Item>
			</SubMenu>
			)
		}else{
			return (
			<Menu.Item key="login">
				<Link to="/login">
					<Icon type="user" />
					<span>Login</span>
				</Link>
			</Menu.Item>
			)
		}
	}

	render() {
		let user = this.getUserMenu()
		
		return (
			<Router>
				<Layout style={{ minHeight: '100vh' }}>
					<Sider collapsible className = 'noSelect' collapsed={this.state.collapsed} onCollapse={this.onCollapse} theme="dark">
						<div className="logo">
							<img className="logo_img" src={ASTA_logo} alt="logo" />
						</div>
						<Menu theme="dark" defaultSelectedKeys={['1']} mode="inline">
							<Menu.Item key="home">
								<Link to="/">
									<Icon type="pie-chart" />
									<span>Home</span>
								</Link>
							</Menu.Item>
							{user}
							<SubMenu
								key="problem"
								title={
									<span>
										<Icon type="bulb" />
										<span>Problem</span>
									</span>
								}
							>
								<Menu.Item key="list" >
									<Link to="/problem">
										<span>List</span>
									</Link>
								</Menu.Item>
								<Menu.Item key="submission" >
									<Link to="/submission">
										<span>Submission</span>
									</Link>
								</Menu.Item>
							</SubMenu>
							<Menu.Item key="Contest">
								<Link to="/contest">
									<Icon type="trophy" />
									<span>Contest</span>
								</Link>
							</Menu.Item>
							<Menu.Item key="Game">
								<Link to="/game">
									<Icon type="robot" />
									<span>Game</span>
								</Link>
							</Menu.Item>
							<Menu.Item key="Blog">
								<Link to="/blog">
									<Icon type="read" />
									<span>Blog</span>
								</Link>
							</Menu.Item>
							<Menu.Item key="Reservation">
								<Link to="/reservation">
									<Icon type="clock-circle" />
									<span>Reservation</span>
								</Link>
							</Menu.Item>
						</Menu>
					</Sider>
					<Layout>
						<Header style={{ background: 'white', padding: 0, display: 'flex', flexDirection: 'row'}} >
							<div style={{ flex: 1 }}>
								<div className = 'noSelect' style={{ flex: 2, fontSize: 25, fontWeight: 'bolder'}}>{Title_word}</div>
								<div>{Tips_word}</div>
							</div>
						</Header>
						<Content style={{ margin: '10px 16px' }}>
							<Route path="/" exact component={Home}/>
							<Route path="/information" render={props => 
								<Information
									user={this.state.user}
									updateUser={this.updateUser.bind(this)}
									{...props} 
								/>}
							/>
							<Route path="/user/:username" render={props => 
								<UserDetail
									user={this.state.user}
									{...props} 
								/>}
							/>
							<Route path="/login" exact render={props =>
								<Login
									unLogin={this.state.user == null}
									updateUser={this.updateUser.bind(this)}
									{...props}
								/>}
							/>
							<Route path="/register" exact render={props =>
								<Register {...props}/>}
							/>
							<Route path="/resetPassword" exact render={props =>
								<ResetPassword 
									logout={this.logout.bind(this)}
								{...props}/>}
							/>
							
							
							<Route path="/contest" exact render={props =>
								<ContestList
									user={this.state.user}
									{...props}
								/>}
							/>
							<Route path="/contest/:id" exact render={props =>
								<ContestDetail
									user={this.state.user}
									{...props}
								/>}
							/>
							<Route path="/contest/:id/:tab" exact render={props =>
								<ContestDetail
									user={this.state.user}
									{...props}
								/>}
							/>
							
							
							<Route path="/blog" exact render={props =>
								<BlogList
									user={this.state.user}
									{...props}
								/>}
							/>
							<Route path="/blog/:id" exact render={props =>
								<BlogDetail
									user={this.state.user}
									{...props}
								/>}
							/>
							<Route path="/blogEdit" exact render={props =>
								<BlogEditor
									user={this.state.user}
									{...props}
								/>}
							/>
							<Route path="/blogEdit/:id" exact render={props =>
								<BlogEditor
									user={this.state.user}
									{...props}
								/>}
							/>
							<Route path="/team" exact render={props =>
								<TeamList
									user={this.state.user}
									{...props}
								/>}
							/>
							<Route path="/reservation" exact render={props =>
								<ReservationList
									{...props} 
								/>}
							/>
							<Route path="/reservation/:id" exact render={props =>
								<ReservationDetail
									user={this.state.user}
									{...props}
								/>}
							/>
							<Route path="/problem" exact render={props =>
								<ProblemList
									user={this.state.user}
									{...props}
								/>}
							/>
							<Route path="/problem/:id" exact render={props =>
								<ProblemDetail
									user={this.state.user}
									{...props}
								/>}
							/>
							<Route path="/contest/:contestId/problem/:id" exact render={props =>
								<ProblemDetail
									user={this.state.user}
									{...props}
								/>}
							/>
							<Route path="/submission" exact render={props =>
								<SubmissionList
									user={this.state.user}
									{...props}
								/>}
							/>
							<Route path="/submission/:id" exact render={props =>
								<SubmissionDetail
									user={this.state.user}
									{...props}
								/>}
							/>
							<Route path="/game" exact render={props =>
								<GameList
									user={this.state.user}
									{...props}
								/>}
							/>
							<Route path="/game/:id" exact render={props =>
								<GameDetail
									user={this.state.user}
									{...props}
								/>}
							/>
							<Route path="/game/:id/:tab" exact render={props =>
								<GameDetail
									user={this.state.user}
									{...props}
								/>}
							/>
							<Route path="/gameShow/:id" exact render={props =>
								<GameShow
									user={this.state.user}
									{...props}
								/>}
							/>
						</Content>
						<Footer className = 'noSelect' style={{ textAlign: 'center' }}>
							&copy; ASTA, 2022 <a href="https://beian.miit.gov.cn/" target="_blank">京ICP备2020038246号</a>
							<div>
								<img src={record_logo} style={{display:'inline'}}/>
								<span><a href="https://www.beian.gov.cn/" target="_blank">京公网安备 11010802033147号</a></span>
							</div>
						</Footer>
					</Layout>
				</Layout>
			</Router>
		);
	}
}

ReactDOM.render(<App />, document.getElementById('container'));