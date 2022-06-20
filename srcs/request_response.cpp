
// GET /form-action.php?color=aaaa&sport=bbbb HTTP/1.1
// Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/avif,image/webp,image/apng,*/*;q=0.8,application/signed-exchange;v=b3;q=0.9
// Accept-Encoding: gzip, deflate, br
// Accept-Language: ko-KR,ko;q=0.9,en-US;q=0.8,en;q=0.7,lb;q=0.6
// Connection: keep-alive
// Host: localhost:8084
// Referer: http://localhost:8084/
// Sec-Fetch-Dest: document
// Sec-Fetch-Mode: navigate
// Sec-Fetch-Site: same-origin
// Sec-Fetch-User: ?1
// Upgrade-Insecure-Requests: 1
// User-Agent: Mozilla/5.0 (Linux; Android 6.0; Nexus 5 Build/MRA58N) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/100.0.4896.127 Mobile Safari/537.36
// sec-ch-ua: " Not A;Brand";v="99", "Chromium";v="100", "Google Chrome";v="100"
// sec-ch-ua-mobile: ?1
// sec-ch-ua-platform: "Android"


// POST /send HTTP/1.1
// Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/avif,image/webp,image/apng,*/*;q=0.8,application/signed-exchange;v=b3;q=0.9
// Accept-Encoding: gzip, deflate, br
// Accept-Language: ko-KR,ko;q=0.9,en-US;q=0.8,en;q=0.7,lb;q=0.6
// Cache-Control: max-age=0
// Connection: keep-alive
// Content-Length: 56
// Content-Type: application/x-www-form-urlencoded
// Host: localhost:8083
// Origin: http://localhost:8083
// Referer: http://localhost:8083/
// Sec-Fetch-Dest: document
// Sec-Fetch-Mode: navigate
// Sec-Fetch-Site: same-origin
// Sec-Fetch-User: ?1
// Upgrade-Insecure-Requests: 1
// User-Agent: Mozilla/5.0 (Linux; Android 6.0; Nexus 5 Build/MRA58N) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/100.0.4896.60 Mobile Safari/537.36
// sec-ch-ua: " Not A;Brand";v="99", "Chromium";v="100", "Google Chrome";v="100"
// sec-ch-ua-mobile: ?1
// sec-ch-ua-platform: "Android"

// name: sdf
// email: sdf@sadfae.com
// subject: sdf
// message: asdf

	/*
void	parsing_request_msg(std::string request_msg)
{
		우리가 유의미하게 해석해야하는 부분은 무엇인가

		1. method // 가장 처음에 나온다. // 없을 수 없다. (우리가 작성하는게 아니므로)
			- method가 유의미한지, 권한이 있는지 체크 (405)
		2. 두번째 location을 포함한 query string
			- 경로외의 정보가 담겨져 있을 수 있다.
			- .php 파일을 요청할 경우 필요 정보가 있어야 한다. (이것을 .php에서 체크를 하는가? -> 그렇겠지)
			- 경로가 유의미한가 확인해야 한다. (404)
		3. HTTP 와 버전이 등장한다.
			- 1.1이 아니면 error를 뱉기로 한다. (?)
		1~3번까지는 맨 처음 줄에 등장한다.

		4. POST method의 경우 body가 등장한다.
		5. body를 체크하기 전에 content-length 체크 혹시나?
		6. body 넣어주기.
}
	*/

	/*
void	making_response_msg()
{
		우리가 해줘야 하는게 무엇인가.
		0. request url 처리를 해주어야 하는가. (CGI가 아닌 경우에)
			- 엔드포인트주소/엔드포인트주소?파라미터=값&파라미터=값 으로 들어와 잘라서 넣어준다? 어디다?
		1. 헤더를 붙여준다.
			- 반드시 붙여줘야 하는 헤더는?
			- 1. 번호 (200, 404, 등)
			- 2. 번호와 함께 가는 메시지(map으로 저장해서 사용)
			- 3. content-length는 필수인가?
			- 4. connection-close를 해주어야 한다. (헤더에 표시하면 브라우저가 인식을 하는가, 아니면 우리가 socket 끊어주면 그걸로 인식을 하는가)

		2. 한 줄 띄운다. (\r\n)
		3. body를 붙여준다.
			- html인 경우 html 고대로 들어가고(개행마다 \r\n 해주는 것?)
			- 에러인 경우 해당 error page html 넣어주고
			- php인 경우 php에서 처리해준 답변을 넣어준다.
				** php에 보내주는 것
				** CGI 처리를 위해 fork를 하고 execve를 하는 것.
				** CGI 처리 후 execve의 반환값을 pipe를 이용해 fd를 조정하고 받아서 저장하는 것
				** 저장된 것을 파싱 혹은 헤더 붙이는 작업 등을 하는 것.
		4. 보내준다.
		5. 보내주고 나서 client 와의 연결은 어떻게 하는가? 끊는가?


		CGI 처리
		1. fork 한다.
		2. fd 입출력을 main 함수로 바꿔준다.
		3. 기본 CGI에 필요한 환경변수 세팅
		4. query string에 있는 값들 환경변수로 넣어준다.
		5. 환경변수를 char** 포인터로 바꿔준다.
		6. argv에 드어가야 하는 것 넣기
		7. 실행한다.
}
	 */

#include <iostream>
#include <vector>
#include <sstream>
#include "../includes/Server.hpp"

// respond, request 헤더를 구분해줄 필요가 있는가?
struct Header
{
	std::string method;
	std::string version;
	std::string url;
	std::string body;
	int 		content_length;
	std::string connection; 
};

struct Client
{
	Server&	server; // 클라이언트 하나 하나마다 server를 참조해서 넣는거 vs 클라이언트들이 있는 벡터가 있는 클래스를 하나 더 만들어서 server도 그 안에서 관리한다.
	Header	header;

	bool	is_cgi = false;

	std::string request_msg;
	std::string respond_msg;
	// char**		envp; // fork 후 execve에서 사용할 envp --> 해당 함수내에서 지역변수로 선언 후 바꾸고 execve 처리 해주는걸루
	std::vector<std::string>	envp;
};

std::vector<std::pair<int, Client> > clients; // socket, Client 구조체 pair



void	validate_header(Client client)
{
	//version check
	if (client.header.version != "HTTP/1.1")
		// 505 HTTP Version Not Supported


	//url check

	// 410 Gone (en-US)

	// method check
	// method 권한 체크를 위해서는
	// url 체크를 먼저 반드시 해주어야 한다.
	int bit_check = 0x0;
	if (client.header.method == "GET" && (client.header.method & client.server.location....))
		;
	else if (client.header.method == "POST" && (client.header.method & client.server.location....))
		;
	else if (client.header.method == "DELETE" && (client.header.method & client.server.location....))
		;
	else
		// 405 Method Not Allowed
		// !!!!! GET은 반드시 존재한다. !!!!!
}

void	parsing_request_header(Client client, std::vector<std::string> request_split)
{
	std::stringstream iss(*request_split.begin());
	std::string temp;
	iss >> client.header.method;
	iss >> client.header.url;
	iss >> client.header.version;
	// std::stringstream iss("");
	for (std::vector<std::string>::iterator iter = ++request_split.begin(); iter != request_split.end(); iter++)
	{
		std::stringstream iss(*iter);
		std::string temp;
		iss >> temp;
		if (temp == "connection")
			iss >> client.header.connection;
		else if (temp == "content-length") // 대문자일경우? Content-length content-Length 들어오는게 한결같은가?
			iss >> client.header.content_length;
	}
}

void	parsing_request_msg(struct Client client)
{
	std::vector<std::string>	request_split;
	std::string					request_body;
	int	from = 0, to = 0;

	while (from < client.request_msg.length())
	{
		to = client.request_msg.find("\r\n", from);
		if (from + 2 < client.request_msg.length() && client.request_msg[from + 2] == '\n')
		{
			request_body = client.request_msg.substr(from + 2);
			break ;
		}
		request_split.push_back(client.request_msg.substr(from, to));
		from = to + 2;
	}

	parsing_request_header(client, request_split);
	validate_header(client);
}

void	making_response_msg(Client client)
{
	int input_fd;
	if (client.is_cgi)
		//cgi 처리기
	else
	{
		//해당 open
		// 파일이 아니라면? index 페이지는 따로 만들어야 하는가
			// - root/route 에 해당 명시된 index 파일들이 없으면 error 인가
		// .파일이라면 html은 html 들고오고
		// php은 .php를 fork로 실행해서 execve로 실행해야 한다.
		// auto index 일때 처리는 어떻게 되는가. (우리가 어떻게 처리해주어야 하는가.)
	}
	// read 해온다
	// client.respond_msg += "200 OK" status_code 붙여준다.
	// client.respond_msg += read 해온 것 (cgi는 cgi 로부터, 혹은 파일로부터)
}
