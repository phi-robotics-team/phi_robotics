
void myflush ( FILE *in )
{
  int ch;

  do
    ch = fgetc ( in );
  while ( ch != EOF && ch != '\n' );

  clearerr ( in );
}
