unsigned long __heap_start;

void
__libc_start_main()
{
	main();
	_exit();
}
