/*
重载
*/

void func(int& a)
{
	putsl 'func int'
}

void func(char& a)
{
	putsl 'func char'
}

void main()
{
	func int()
	func char()
}