#########################################################################
# cygwin_ck

  cygwin用のターミナルエミュレータ。インストール方法や使い方は、
  配布元 http://www.geocities.jp/meir/ を参照してください。

  このソフトウェアのライセンスは GNU General Public Licenseです。
  詳細は COPYING.txt、 http://www.gnu.org/licenses/ を参照してください。


#########################################################################
# コンパイル

  コンパイルに cygwinは一切必要ありません。
  Windows SDK v6.0だけ用意すればコンパイル出来ます。

  Windows SDKはこちらからダウンロードできます。
    Microsoft® Windows® Software Development Kit Update for Windows Vista™
    http://www.microsoft.com/downloads/details.aspx?familyid=4377f86d-c913-4b5c-b87e-ef72e5b4e065&displaylang=en

  Visual Studio 2005に付属する Platform SDKではヘッダーファイル等が古くてコンパイル出来ません。
  Windows SDKにコンパイラも付属しているので Visual Studio 2005も要りません。
  IDEとして Visual Studio 2005を使う場合でも、include, lib, cl.exe, link.exe, rc.exe など
  全て Windows SDKの物を使うように設定すること。


  Windows SDKをインストールしたら、スタートメニューから。
  StartMenu -> All Program -> Microsoft Windows SDK -> CMD Shell

    cd /d C:\download\ck-3.2.0\ [enter]
    nmake.exe [enter]

  これでOK。
  Intel Compilerでコンパイルする場合はMakefileを書き換えて下さい。


#########################################################################
# その他

  文字コード変換テーブル(encoding_table.cpp)は .NET frameworkのデータからC#で生成しています。
    csc.exe gen_enc.cs [enter]
    gen_enc.exe [enter]
