our %EXPORT_TAGS = ('censura'=>[qw()]);
our @EXPORT_OK = (@{$EXPORT_TAGS{'all'}});
use warnings;

sub censurar{
  my ($input,$output)=@_;
  #-------------------------Registro de palavrões------------------------------------#
  open (my $inp, "<",'PALAVROES.txt') or die "Arquivo PALAVROES não encontrado. $!";
  my $nlinesp;
  $nlinesp++ while (<$inp>);
  seek($inp,0,0);
  my @palavroes;
  for(my $p=0;$p < $nlinesp ;$p++)
  {
  $palavroes[$p]=<$inp>;
  chomp($palavroes[$p]);
  }
  close $inp;

  #-------------------------Criação de Censuras-------------------------------------#
  my @censuras;
  for(my $num = 0; $num < (scalar @palavroes); $num++){
    
    my $size=length($palavroes[$num]);
    
    $censuras[$num] = substr $palavroes[$num],0,1;
    
    if($palavroes[$num]=~/\[...\]/){
      $size=$size-4;
    }
    elsif($palavroes[$num]=~/\[..\]/){
      $size=$size-3;
    }
    
    for (my $cen = 0; $cen < ($size-1); $cen++) {
      $censuras[$num]=~s/$/*/gi;
    }
  }
  #-------------------------Substituindo as palavras--------------------------------#
  open (my $in, "<","$input") or die "Não foi possível abrir o arquivo: $!";
  $nlines++ while (<$in>);
  print "\n";
  seek($in,0,0);
  my $line;
  
  for(my $x=0;$x<$nlines;$x++)
  {
    $line[$x]=<$in>;
    for(my $y=0;$y<(scalar @palavroes);$y++)
    {
      $line[$x] =~ s/$palavroes[$y]\b/$censuras[$y]/gi;
    }
    #print "$line[$x]\n";
  }
  
  close $in or die "Não foi possível fechar o arquivo: $!";
  
  #-------------------------Escrita do novo arquivo censurado-------------------------#

  open (my $out, ">","$output") or die "Não foi possível abrir o arquivo: $!";
  for(my $x=0;$x<$nlines;$x++)
  {
    print $out $line[$x];
  }
  print "\n";
  
  print "Arquivo \"$output\" criado.\n\n";
  close $out or die "Não foi possível fechar o arquivo: $!";
}
 
 
1;