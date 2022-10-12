global.constants = {
    //server:'https://fcapi.thu-ai.net/',
    // server:'http://127.0.0.1:8000/',
    //server:'http://166.111.73.151:8002/',
    //server:'http://182.92.230.1:81/',
    //server:'http://www.thuasta.cn:81/',
    server:'https://www.thuasta.cn:8000/',
};

export function getColorFromStatus(status){
	let color = 'red';
	switch (status.toUpperCase()){
		case 'WAITING': color = 'cyan';break;
		case 'JUDGING': color = 'orange';break;
		case 'ACCEPT': color = 'green';break;
		case 'FINISH': color = 'green';break;
		case 'SYSTEMERROR': color = 'magenta';break;
		case 'COMPILEERROR': color = 'volcano';break;
		case 'COMPILETIMEOUT': color = 'volcano';break;
		case 'COMPILING': color = 'gold';break;
	}
	return color;
}
