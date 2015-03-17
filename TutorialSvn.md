# Introduction #

O controle de versao possibilitara que todos tenham os mesmos arquivos no computador, assim ao fazer alteracoes no codigo fonte teremos certeza de que nao vamos perder a parte de ninguem e etc.

# Linux #

Utilizaremos o svn.

**checkout - eh a operacao de baixar os arquivos do repositorio para o computador**

  * crie uma pasta ex: mkdir MC326

  * copie o comando do link http://code.google.com/p/mc326ef-g15/source/checkout e qnd perguntado utilize a senha no link logo abaixo
> > ex: svn checkout https://mc326ef-g15.googlecode.com/svn/trunk/ mc326ef-g15 --username Helen.Fornazier

**checkin - eh a operacao de enviar os arquivos para o repositorio e criar uma nova versao**

  * se criar algum arquivo novo, use o comando svn add "nome do arquivo ou diretorio"
isso fara com que os arquivos facao parte dessa revisao

  * utilize o comando svn ci -m "resumo de operacoes efetuadas" assim sera enviado os arquivos ao repositorio.
sempre coloque um resumo para ficar mais facil o controle de versao

# Windows #

Vao precisar do Tortoise SVN
O tutorial de como utiliza-lo eh esse
http://internetducttape.com/2007/03/03/howto_google_code_hosting_subversion_tortoisesvn/

# Details #

Add your content here.  Format your content with:
  * Text in **bold** or _italic_
  * Headings, paragraphs, and lists
  * Automatic links to other wiki pages