#########################################################################
# cygwin_ck

  Cygwin 用のターミナルエミュレータ。インストール方法や使い方は、
  配布元 http://www.geocities.jp/meir/ を参照してください。

  このソフトウェアのライセンスは GNU General Public License です。
  詳細は COPYING.txt、http://www.gnu.org/licenses/ を参照してください。


#########################################################################
# コンパイル

  コンパイルに Cygwin は一切必要ありません。
  Windows SDK v6.0、または Visual C++ 2008 (Express Editionで可) を用意すればコンパイル出来ます。

  Windows SDK はこちらからダウンロードできます。
    Microsoft® Windows® Software Development Kit Update for Windows Vista™
    http://www.microsoft.com/downloads/details.aspx?familyid=4377f86d-c913-4b5c-b87e-ef72e5b4e065&displaylang=en

  Microsoft Visual C++ 2008 Express Edition はこちらから。
    http://www.microsoft.com/japan/msdn/vstudio/express/

  Visual Studio 2005 に付属する Platform SDK ではヘッダーファイル等が古くてコンパイル出来ません。
  Windows SDK にコンパイラも付属しているので Visual Studio 2005 も要りません。
  IDE として Visual Studio 2005 を使う場合でも、include, lib, cl.exe, link.exe, rc.exe など
  全て Windows SDK の物を使うように設定すること。


  Windows SDKをインストールしたら、スタートメニューから。
  StartMenu -> All Program -> Microsoft Windows SDK -> CMD Shell

    cd /d C:\download\ck-3.2.0\ [Enter]
    nmake.exe [Enter]

  これで OK。
  Intel Compiler でコンパイルする場合は Makefile を書き換えて下さい。


#########################################################################
# その他

  文字コード変換テーブル (encoding_table.cpp) は .NET Framework のデータから C# で生成しています。

    csc.exe gen_enc.cs [Enter]
    gen_enc.exe [Enter]
