//ヘッダーファイルのインクルード　ひとまずおまじないとして書いておく
//ROOT関連
#include <TFile.h>
#include <TTree.h>
#include <TCanvas.h>
#include <TH1.h>
#include <TH2.h>
#include <TGraph.h>
//C++関連
#include <iostream>


//メインの関数　※ROOTのマクロはファイル名(拡張子を除く)と同じ名前の関数が実行される
void plot_epair_manyfile1(){

    //ヒストグラムの定義
    TH1D *h_gax = new TH1D("h_gax", "gax;tan#theta_{X};entries", 100, -1.5, 1.5);

    TH2D *h_gang = new TH2D("h_gang", "angle;tan#theta_{X};tan#theta_{Y}", 100, -1.5, 1.5, 100, -1.5, 1.5);

    //TGraphの定義
    TGraph *g_entry = new TGraph();
    g_entry->SetTitle(";PL;entries");
    g_entry->SetMarkerStyle(8);
    g_entry->SetMarkerColor(kRed);

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

    g_entry->SetPoint(0, 5, entries);
    //g_entry->SetPoint(点番号, xの値, yの値);

    //繰り返す　PL006
    TFile *f2 = new TFile("../../PL006/6-EventAbs/EventAbsUnit5PL006-006.root", "read");
    TTree *t2 = (TTree*)f2->Get("t");

    entries = t2->GetEntries(); //entriesという変数はすでに定義されているので二重で定義しないように
    std::cout << "Entries : " << entries << std::endl;

    //double gax, gay; //entriesと同様にすでに定義しているのでいらない

    t2->SetBranchAddress("gax", &gax);
    t2->SetBranchAddress("gay", &gay);

    for(int i = 0; i < entries; i++){
        t2->GetEntry(i);

        h_gax->Fill(gax);
        h_gang->Fill(gax, gay);
    }
    f2->Close();

    g_entry->SetPoint(1, 6, entries);

    //繰り返す　PL007
    TFile *f3 = new TFile("../../PL007/6-EventAbs/EventAbsUnit5PL007-007.root", "read");
    TTree *t3 = (TTree*)f3->Get("t");

    entries = t3->GetEntries(); //entriesという変数はすでに定義されているので二重で定義しないように
    std::cout << "Entries : " << entries << std::endl;

    //double gax, gay; //entriesと同様にすでに定義しているのでいらない

    t3->SetBranchAddress("gax", &gax);
    t3->SetBranchAddress("gay", &gay);

    for(int i = 0; i < entries; i++){
        t3->GetEntry(i);

        h_gax->Fill(gax);
        h_gang->Fill(gax, gay);
    }
    f3->Close();

    g_entry->SetPoint(2, 7, entries);

    TCanvas *c = new TCanvas("c", "c", 800, 600);

    c->Print("epair_manyfile1.pdf[");

    h_gax->Draw();
    c->Print("epair_manyfile1.pdf");
    c->Clear();

    h_gang->Draw("colz");
    c->Print("epair_manyfile1.pdf");
    c->Clear();

    g_entry->Draw("AP");
    //A：axis, P：point, L：line
    c->Print("epair_manyfile1.pdf");
    c->Clear();

    c->Print("epair_manyfile1.pdf]"); //pdfを閉じる

}