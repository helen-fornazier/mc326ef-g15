# Introduction #
# Tut Prático #

# Instalando #
Para instalar o svn (subversion) digite:
> sudo apt-get install subversion

# Downloading File #
> Para baixar os arquivos digite em um apasta qualquer em que pretende armazenar os arquivos o comando que esta escrito na aba Source (http://code.google.com/p/mc326ef-g15/source/checkout) e a senha que está em um link abaixo.

Obs: este comando só é necessário uma vez, as outras vezes é só svn update que ele atualiza os arquivos

> Para atualizar digite     svn up

# Uploading File #
> Para mandar as mudanças do arquivo modificado digite:
> > svn ci -m "Mudei a função tal .. e fiz tal coisa"


> Obs: este comando só manda os arquivos que estão marcados como arquivos a serem atualizados

> Para marcar outro arquivo ou pasta é só digitar:
> > svn add arquivo/pasta

> Agora quanda você der   svn ci -m "fiz bla bla bla"   o arquivo que vc atualizou será mandado para o code.google

> Obs: se não escrever -m "bla bla bla" não dá certo. E o "bla bla bla" é bom pra saber o que foi modificado

> Obs: Você só pode mandar arquivos que estejam nesta pasta, ou seja, para mandar um outro arquivo qualquer, copie o arquivo para esta pasta (mc326ef-g15, ou uma pasta mais interior que você queira mandar), dê um svn add [arquivo](arquivo.md) e um svn ci -m "bla bla"

# Proposta #
> Toda vez que for programar dar um     svn up
> E depois de modificar dar um          svn ci -m "bla bla"

> Assim ninguém faz modificaçõe em arquivos separados, dando um trabalhão depois pra juntar as modificações.





# Details #

Add your content here.  Format your content with:
  * Text in **bold** or _italic_
  * Headings, paragraphs, and lists
  * Automatic links to other wiki pages