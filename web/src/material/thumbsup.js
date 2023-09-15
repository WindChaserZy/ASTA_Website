import '../config';
import { Link } from 'react-router-dom';
import $ from 'jquery';
import {Button,Tooltip } from 'antd';
import React, { Component } from 'react';
import './thumbsup.css';

class ThumbsUp extends Component
{   
    state = {
            isLiked: false,     //有用
            isFunny: false,     //欢乐
            isDisliked: false,  //没有用
            num_liked: 0,
            num_funny: 0,
            num_dislike:0,
        }
    constructor(props)
    {
        this.onclick_like = this.onclick_like.bind(this);
        this.onclick_funny = this.onclick_funny.bind(this);
        this.onclick_dislike = this.onclick_dislike.bind(this);
    }
    

    componentWillMount()
    {
        //TODO:get state from the backside
        //向后端发送当前笔记的标识码
        //从后端得到当前笔记的点赞数、欢乐数、没有用数
        //从后端得到当前用户对当前笔记的观点
    }

    onclick_like()
    {
        if (isLiked)
        {
            this.setState({
                isLiked: false,
                num_liked: num_liked-1
		    });
        }
        else
        {
            this.setState({
                isLiked: true,
                num_liked: num_liked + 1,
                isDisliked:false
		    });       
        }
        this.update();
        return;
    }

    onclick_funny()
    {
        if (isFunny)
        {
            this.setState({
                isFunny: false,
                num_funny:num_funny-1
		    });
        }
        else
        {
            this.setState({
                isFunny: true,
                num_funny: num_funny + 1
		    });
            
        }
        this.update();
        return;
    }

    onclick_dislike()
    {
        if (isDisliked)
        {
            this.setState({
                isDisliked: false,
                num_dislike:num_dislike-1
		    });
        }
        else
        {
            this.setState({
                isDisliked: true,
                num_dislike: num_dislike + 1,
                isLiked:true
		    });
            
        }
        this.update();
        return;
    }

    update()
    {
        //TODO: update the states to the backside
    }

    render() {
        var btn_liked, btn_funny, btn_disliked;
        if (this.state.isLiked)
        {
            btn_liked = <Button shape="circle" type="primary" icon={<LikeOutlined />} onClick={onclick_like} />
        }
        else
        {
            btn_liked = <Button shape="circle" icon={<LikeOutlined />} onClick={onclick_like} />
        }
        
        if (this.state.isFunny)
        {
            btn_funny = <Button shape="circle" type="primary" icon={<SmileOutlined />} onClick={onclick_funny} />
        }
        else
        {
            btn_funny = <Button shape="circle" icon={<SmileOutlined />} onClick={onclick_funny} />
        }
        
        if (this.state.isDisliked)
        {
            btn_disliked = <Button shape="circle" type="primary" icon={<FrownOutlined />} onClick={onclick_dislike} />
        }
        else
        {
            btn_disliked = <Button shape="circle" icon={<FrownOutlined />} onClick={onclick_dislike} />
        }
        
        return (
            <div>
                <div>
                    <p>有[{this.state.num_liked}]人觉得这篇笔记有用</p>
                    <p>有[{this.state.num_funny}]人觉得这篇笔记很欢乐</p>
                    <p>有[{this.state.num_dislike}]人觉得这篇笔记没有用</p>
                </div>

                <div>
                    <Tooltip title="有用">
                        {btn_liked}
                    </Tooltip>
                      
                    <Tooltip title="欢乐">
                        {btn_funny}
                    </Tooltip>
                 
                    <Tooltip title="没有用">
                        {btn_disliked}
                    </Tooltip>
                </div>
            </div>
        )
    }
}
export default ThumbsUp;