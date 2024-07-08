/*
easy reference

TH1D *h = new TH1D(HistName, Title("title;xlabel;ylabel")), x_bins, x_min, x_max)
TH2D *h = new TH2D(HistName, Title("title;xlabel;ylabel;zlabel")), x_bins, x_min, x_max, y_bins, y_min, y_max)
TFile *f = new TFile(FileName, Option);
TTree *t = (TTree*)f->Get(TreeName);
t->SetBranchAddress(BranchName, &VarName);
TCanvas *c = new TCanvas(name, title, xsize, ysize)

*/

//ヘッダーファイルのインクルード　ひとまずおまじないとして書いておく
//ROOT関連
#include <TFile.h>
#include <TTree.h>
#include <TCanvas.h>
#include <TH1.h>
#include <TH2.h>
//C++関連
#include <iostream>


//メインの関数　※ROOTのマクロはファイル名(拡張子を除く)と同じ名前の関数が実行される
void plot_epair1file(){

    //ヒストグラムの定義
    TH1D *h_gax = new TH1D("h_gax", "gax;tan#theta_{X};entries", 100, -1.5, 1.5);

    TH2D *h_gang = new TH2D("h_gang", "angle;tan#theta_{X};tan#theta_{Y}", 100, -1.5, 1.5, 100, -1.5, 1.5);

    //rootfileを開く
    TFile *f = new TFile("../../PL005/6-EventAbs/EventAbsUnit5PL005-005.root", "read"); //rootfileを開く
    TTree *t = (TTree*)f->Get("t"); //fの中の"t"という名前のtreeを開く

    int entries = t->GetEntries(); //treeのエントリー数を取得
    std::cout << "Entries : " << entries << std::endl; //コマンドプロンプトに出力

    //各イベントの中身を入れるための変数を定義
    double gax, gay;

    //どのBranchの中身をどの変数に詰め込むかを定義
    t->SetBranchAddress("gax", &gax);
    t->SetBranchAddress("gay", &gay);

    //for-loopで全エントリーの中身を読み込む
    for(int i = 0; i < entries; i++){
        t->GetEntry(i); //i番目のエントリーの値を各変数に詰め込む

        h_gax->Fill(gax);//値を詰め込む
        h_gang->Fill(gax, gay);
    }
    f->Close();//メモリの解放(少しマニアックだが重要)

    TCanvas *c = new TCanvas("c", "c", 800, 600); //canvasを定義

    c->Print("epair1file.pdf["); //pdfを開く*最後に閉じるのを忘れない

    h_gax->Draw(); //canvasにhistを描画
    c->Print("epair1file.pdf"); //ページを出力
    c->Clear(); //canvasに描いてあるものを消去

    h_gang->Draw("colz"); //colzオプションは2次元ヒストグラムをカラーバーで表現する時に使う。つけないと散布図になる
    c->Print("epair1file.pdf");
    c->Clear();

    c->Print("epair1file.pdf]"); //pdfを閉じる

}

/*
**************
**　　宿題　　**
**************

1. gayの一次元ヒストグラムを描く
2. genergyの一次元ヒストグラムを描く
3. ガンマ線イベントの位置分布(gax, gay)の2次元ヒストグラムを描く

*/

