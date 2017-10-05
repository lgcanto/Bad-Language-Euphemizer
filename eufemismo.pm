our %EXPORT_TAGS = ('eufemismo'=>[qw()]);
our @EXPORT_OK = (@{$EXPORT_TAGS{'all'}});
use warnings;

sub eufemizar{
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

  #-------------------------Registro de eufemismos Gerais----------------------------#
  open (my $ine, "<",'EUFEMISMOS.txt') or die "Arquivo EUFEMISMOS não encontrado. $!";
  my $nlinese;
  $nlinese++ while (<$ine>);
  seek($ine,0,0);
  my @eufemismos;
  for(my $e=0;$e<$nlinese;$e++)
  {
  $eufemismos[$e]=<$ine>;
  chomp($eufemismos[$e]);
  }
  close $ine;
  #-------------------------Substituindo as palavras---------------------------------#
  open (my $in, "<","$input") or die "Não foi possível abrir o arquivo: $!";
  my $nlines2;
  $nlines2++ while (<$in>);
  print "\n";
  seek($in,0,0);
  my $line;
  
  for(my $x=0;$x<$nlines2;$x++)
  {
    $line[$x]=<$in>;
    # seu....
    if($line[$x]=~/(s[eu][au]||aquel[ea]||um||uma) ($palavroes[0]\b||$palavroes[1]\b||$palavroes[2]\b||$palavroes[3]\b)/i){
        $line[$x] =~ s/seu ($palavroes[0]\b|$palavroes[1]\b|$palavroes[2]\b|$palavroes[3]\b|$palavroes[4]\b)/seu idiota/gi;
        $line[$x] =~ s/sua ($palavroes[0]\b|$palavroes[1]\b|$palavroes[2]\b|$palavroes[3]\b|$palavroes[4]\b)/sua idiota/gi;
        $line[$x] =~ s/aquele ($palavroes[0]\b|$palavroes[1]\b|$palavroes[2]\b|$palavroes[3]\b|$palavroes[4]\b)/aquele idiota/gi;
        $line[$x] =~ s/aquela ($palavroes[0]\b|$palavroes[1]\b|$palavroes[2]\b|$palavroes[3]\b|$palavroes[4]\b)/aquela idiota/gi;
        $line[$x] =~ s/um ($palavroes[0]\b|$palavroes[1]\b|$palavroes[2]\b|$palavroes[3]\b|$palavroes[4]\b)/um idiota/gi;
        $line[$x] =~ s/uma ($palavroes[0]\b|$palavroes[1]\b|$palavroes[2]\b|$palavroes[3]\b|$palavroes[4]\b)/uma idiota/gi;
    }
    if($line[$x]=~/é $palavroes[19]\b/i){
        $line[$x] =~ s/é $palavroes[19]\b/é complicado/gi;
    }
    # filho da....
    if($line[$x]=~/filh[ao] da $palavroes[4]\b/i){
        $line[$x] =~ s/filho da $palavroes[4]\b/filho da mãe/gi;
        $line[$x] =~ s/filha da $palavroes[4]\b/filha da mãe/gi;
    }    
    # vai se....
    if($line[$x]=~/vai (pra $palavroes[4] que pariu\b||tomar no $palavroes[8]\b)/i){
        $line[$x] =~ s/(pra $palavroes[4] que pariu\b|tomar no $palavroes[8]\b)/se ferrar/gi;
    }
    # que...
    if($line[$x]=~/($palavroes[4] $palavroes[1]\b||$palavroes[4] que pariu\b)/i){
        $line[$x] =~ s/($palavroes[4] $palavroes[1]\b|$palavroes[4] que pariu\b)/que droga/gi;
    }
    #eufemismos gerais
    for(my $y=0;$y<(scalar @palavroes);$y++)
    {
      $line[$x] =~ s/$palavroes[$y]\b/$eufemismos[$y]/gi;
    }
    #print "$line[$x]\n";
  }
  
  close $in or die "Não foi possível fechar o arquivo: $!";
  
  #-------------------------Escrita do novo arquivo eufemizado-------------------------#

  open (my $out, ">","$output") or die "Não foi possível abrir o arquivo: $!";
  for(my $x=0;$x<$nlines2;$x++)
  {
    print $out $line[$x];
  }
  print "\n";
  
  print "Arquivo \"$output\" criado.\n\n";
  close $out or die "Não foi possível fechar o arquivo: $!";
}
 
 
1;