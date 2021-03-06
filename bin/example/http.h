/*
简单的http服务器，参考《深入理解计算机系统》
运行后在浏览器输入http://127.0.0.1/example/1.h
*/

import rsock.h
import rfile.h
import rdir.h

main
{
	rsock svr
	rsock client
	svr.listen(80)
	for svr.accept(client)	
		proc(client,client.recv_s(65536))
		client.close
}

class http_item
{
	rstr name
	rstr cont
}

proc(rsock& client,rstr& s)
{
	s.print
	vstr=s.split('\r\n')
	rbuf<http_item> vitem
	for i in vstr
		pos=vstr[i].find(' ')
		http_item item
		item.name=vstr[i].sub(0,pos)
		item.cont=vstr[i].sub(pos+1)
		vitem+=item
	proc(client,vitem)
}

proc(rsock& client,rbuf<http_item>& v)
{
	if v.empty||v.get(0).name!='GET'
		return
	path=v[0].cont.sub(0,v[0].cont.find(' '))
	path='.'+path
	rfile file(path)
	s='HTTP/1.1 200 OK\r\n'
	s+='Server: RPP Web Server\r\n'
	s+='Content-Length: '+file.size+'\r\n'
	s+='Content-type: '+get_type(path)+'\r\n\r\n'
	s+=file.read_all
	client.send_s(s)
}

rstr get_type(rstr name)
{
	name=rdir.get_suffix(rdir.get_name(name))
	if name=='htm'||name=='html'
		return 'text/html'
	elif name=='gif'
		return 'image/gif'
	elif name=='jpg'
		return 'image/jpg'
	else
		return 'text/plain'
}