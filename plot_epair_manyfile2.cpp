//ヘッダーファイルのインクルード　ひとまずおまじないとして書いておく
//ROOT関連
#include <TFile.h>
#include <TTree.h>
#include <TCanvas.h>
#include <TH1.h>
#include <TH2.h>
#include <TGraph.h>
#include <TString.h>
//C++関連
#include <iostream>


//メインの関数　※ROOTのマクロはファイル名(拡張子を除く)と同じ名前の関数が実行される
void plot_epair_manyfile2(){

    //ヒストグラムの定義
    TH1D *h_gax = new TH1D("h_gax", "gax;tan#theta_{X};entries", 100, -1.5, 1.5);

    TH2D *h_gang = new TH2D("h_gang", "angle;tan#theta_{X};tan#theta_{Y}", 100, -1.5, 1.5, 100, -1.5, 1.5);

    //TGraphの定義
    TGraph *g_entry = new TGraph();
    g_entry->SetTitle(";PL;entries");
    g_entry->SetMarkerStyle(8);
    g_entry->SetMarkerColor(kRed);

    //変数の宣言はfor-loopの外でする
    int entries;
    double gax, gay;
    int count_plot = 0;

    for(int pl = 5; pl <= 10; pl++){
        std::cout << "PL" << pl << std::endl;
        TFile *f = new TFile(Form("../../PL%03d/6-EventAbs/EventAbsUnit5PL%03d-%03d.root", pl, pl, pl));
        //Formを使うと文字列に数値などを代入した文字列を作れる(ROOTの関数)
        TTree *t = (TTree*)f->Get("t");

        entries = t->GetEntries();
        std::cout << "Entries : " << entries << std::endl;

        t->SetBranchAddress("gax", &gax);
        t->SetBranchAddress("gay", &gay);

        for(int i = 0; i < entries; i++){
            t->GetEntry(i);

            h_gax->Fill(gax);
            h_gang->Fill(gax, gay);
        }
        f->Close();

        g_entry->SetPoint(count_plot, pl, entries);
        count_plot++;

    }

    TCanvas *c = new TCanvas("c", "c", 800, 600);

    c->Print("epair_manyfile2.pdf[");

    h_gax->Draw();
    c->Print("epair_manyfile2.pdf");
    c->Clear();

    h_gang->Draw("colz");
    c->Print("epair_manyfile2.pdf");
    c->Clear();

    g_entry->Draw("AP");
    //A：axis, P：point, L：line
    c->Print("epair_manyfile2.pdf");
    c->Clear();

    c->Print("epair_manyfile2.pdf]"); //pdfを閉じる

}