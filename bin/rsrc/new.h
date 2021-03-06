
rp<T> r_new<T>(int count)
{
	p=rf::malloc(sizeof(int)+count*sizeof(T))
	if(p==null)
	{
		rf.error("memory insufficient")
		mov s_ret,p
		return
	}
	mov esi,p
	mov [esi],count
	p+=sizeof(int)
	start=p
	for(i=0;i<count;i++)
	{
		T& t
		mov t,p
		T.T(t)
		p+=sizeof(T)
	}
	mov s_ret,start
}

rp<T> r_new_n<T>(int count)
{
	p=rf::malloc(sizeof(int)+count*sizeof(T))
	if(p==null)
	{
		rf.error("memory insufficient")
		mov s_ret,p
		return
	}
	mov esi,p
	mov [esi],count
	p+=sizeof(int)
	start=p
	mov s_ret,start
}

r_delete<T>(rp<T> p)
{
	char* start=p
	start-=sizeof(int)
	int count
	mov esi,start
	mov count,[esi]
	start+=sizeof(int)
	for(i=0;i<count;i++)
	{
		T& t
		mov t,start
		T.~T(t)
		start+=sizeof(T)
	}
	mov start,p
	start-=sizeof(int)
	rf::mfree start
}

r_delete_n<T>(rp<T> p)
{
	char* start=p
	start-=sizeof(int)
	int count
	mov esi,start
	mov count,[esi]
	start+=sizeof(int)
	mov start,p
	start-=sizeof(int)
	rf::mfree start
}