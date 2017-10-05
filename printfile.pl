sub printfile{
	my ($input)=@_;
	open (my $in, "<","$input") or die "Can't open the file: $!";
	#printa todas as linhas
	my @lines=<$in>;
	print @lines;
	close $in or die "Cant close the file: $!";
	print "\n";
}