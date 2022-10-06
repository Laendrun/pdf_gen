#include "laendrun.h"

void pdf_add_header(struct pdf_doc *pdf, char *logo_path){
    pdf_add_text(pdf, NULL, "Laendrun", 10, PDF_MM_TO_POINT(12), PDF_MM_TO_POINT(275), PDF_BLACK);
    pdf_add_text(pdf, NULL, "Ch. de la Chapelle 4", 8, PDF_MM_TO_POINT(12), PDF_MM_TO_POINT(270), PDF_BLACK);
    pdf_add_text(pdf, NULL, "1617 Remaufens", 8, PDF_MM_TO_POINT(12), PDF_MM_TO_POINT(265), PDF_BLACK);
    pdf_add_text(pdf, NULL, "T +41 79 193 09 41", 8, PDF_MM_TO_POINT(12), PDF_MM_TO_POINT(260), PDF_BLACK);
    pdf_add_text(pdf, NULL, "contat@laendrun.ch", 8, PDF_MM_TO_POINT(75), PDF_MM_TO_POINT(265), PDF_BLACK);
    pdf_add_text(pdf, NULL, "www.laendrun.ch", 8, PDF_MM_TO_POINT(75), PDF_MM_TO_POINT(260), PDF_BLACK);
    pdf_add_image_file(pdf, NULL, PDF_MM_TO_POINT(150), PDF_MM_TO_POINT(259), PDF_MM_TO_POINT(50), PDF_MM_TO_POINT(22), logo_path);
}

int pdf_add_dest_adr(struct pdf_doc *pdf, int mm, char cust_no[20], char name[50], char name2[50], char adr[100], char adr2[100], char city[50], char npa[10]){
    char citynpa[60] = "";
    strcat(citynpa, npa);
    strcat(citynpa, " ");
    strcat(citynpa, city);
    pdf_add_text(pdf, NULL, cust_no, 12, LEFT_MARGIN, PDF_MM_TO_POINT(mm), PDF_BLACK);
    mm = mm-5;
    pdf_add_text(pdf, NULL, name, 12, LEFT_MARGIN, PDF_MM_TO_POINT(mm), PDF_BLACK);
    if (strcmp(name2, "") != 0){
        mm = mm-5;
        pdf_add_text(pdf, NULL, name2, 12, LEFT_MARGIN, PDF_MM_TO_POINT(mm), PDF_BLACK);
    }
    if (strcmp(adr, "") != 0){
      mm = mm-5;
      pdf_add_text(pdf, NULL, adr, 12, LEFT_MARGIN, PDF_MM_TO_POINT(mm), PDF_BLACK);
    }
    if (strcmp(adr2, "") != 0){
        mm = mm-5;
        pdf_add_text(pdf, NULL, adr2, 12, LEFT_MARGIN, PDF_MM_TO_POINT(mm), PDF_BLACK);
    }
    mm = mm-5;
    pdf_add_text(pdf, NULL, citynpa, 12, LEFT_MARGIN, PDF_MM_TO_POINT(mm), PDF_BLACK);
    mm = mm-10;

    return mm;
}

void pdf_add_lines_header(struct pdf_doc *pdf, int mm){

    pdf_add_text(pdf, NULL, "N° art.", 12, ART_NO_XOFF, PDF_MM_TO_POINT(mm), PDF_BLACK);
    pdf_add_text(pdf, NULL, "Désignation", 12, DESC_XOFF, PDF_MM_TO_POINT(mm), PDF_BLACK);
    pdf_add_text(pdf, NULL, "Qté", 12, QTY_XOFF, PDF_MM_TO_POINT(mm), PDF_BLACK);
    pdf_add_text(pdf, NULL, "Prix Unit.", 12, UNIT_PRICE_XOFF, PDF_MM_TO_POINT(mm), PDF_BLACK);
    pdf_add_text(pdf, NULL, "Montant", 12, AMOUNT_XOFF, PDF_MM_TO_POINT(mm), PDF_BLACK);
    mm = mm-3;
    pdf_add_line(pdf, NULL, PDF_MM_TO_POINT(18), PDF_MM_TO_POINT(mm), PDF_MM_TO_POINT(192), PDF_MM_TO_POINT(mm), 0.5, PDF_BLACK);
    mm = mm-5;
}

void pdf_add_doc_no(struct pdf_doc *pdf, int mm, char doc_type[4], char doc_no[20]){
    char doc_txt[100]="";

    if(strcmp(doc_type, "0") == 0) {
      strcat(doc_txt, "Offre N° OC");
    }else if (strcmp(doc_type, "1") == 0){
      strcat(doc_txt, "Confirmation de commande N° CV");
    }else if (strcmp(doc_type, "2") == 0){
      strcat(doc_txt, "Facture N° FA");
    }
    strcat(doc_txt, doc_no);
    pdf_add_text(pdf, NULL, doc_txt, 12, LEFT_MARGIN, PDF_MM_TO_POINT(mm), PDF_BLACK);
}

void pdf_add_total_line(struct pdf_doc *pdf, float f_total_amount, int mm){
    char c_total_amount[50];
    gcvt(f_total_amount, 10, c_total_amount);
    mm = mm-3;
    pdf_add_line(pdf, NULL, PDF_MM_TO_POINT(172), PDF_MM_TO_POINT(mm), PDF_MM_TO_POINT(192), PDF_MM_TO_POINT(mm), 0.5, PDF_BLACK);
    mm = mm-7;
    pdf_add_text(pdf, NULL, "Total TTC (CHF):", 12, TOTAL_XOFF, PDF_MM_TO_POINT(mm), PDF_BLACK);
    pdf_add_text(pdf, NULL, c_total_amount, 12, AMOUNT_XOFF, PDF_MM_TO_POINT(mm), PDF_BLACK);
    mm = mm-3;
    pdf_add_line(pdf, NULL, PDF_MM_TO_POINT(172), PDF_MM_TO_POINT(mm), PDF_MM_TO_POINT(192), PDF_MM_TO_POINT(mm), 0.5, PDF_BLACK);
    mm = mm-1;
    pdf_add_line(pdf, NULL, PDF_MM_TO_POINT(172), PDF_MM_TO_POINT(mm), PDF_MM_TO_POINT(192), PDF_MM_TO_POINT(mm), 0.5, PDF_BLACK);
}

void pdf_add_invoice_page(struct pdf_doc *pdf, float f_total_amount, char * twint_qr_path, char * twint_dir_path, char * logo_path){
    pdf_append_page(pdf);
    pdf_add_header(pdf, logo_path);

    pdf_add_image_file(pdf, NULL, PDF_MM_TO_POINT(50), PDF_MM_TO_POINT(115), PDF_MM_TO_POINT(55), PDF_MM_TO_POINT(84), twint_qr_path);
    pdf_add_image_file(pdf, NULL, PDF_MM_TO_POINT(105), PDF_MM_TO_POINT(115), PDF_MM_TO_POINT(55), PDF_MM_TO_POINT(84), twint_dir_path);

    char c_amount_to_pay[75];
    char c_total_amount[50];
    gcvt(f_total_amount, 10, c_total_amount);
    strcat(c_amount_to_pay, "Montant à payer : ");
    strcat(c_amount_to_pay, c_total_amount);

    pdf_add_text(pdf, NULL, c_amount_to_pay, 12, PDF_MM_TO_POINT(18), PDF_MM_TO_POINT(70), PDF_BLACK);
    pdf_add_text(pdf, NULL, "Merci de votre confiance.", 12, PDF_MM_TO_POINT(18), PDF_MM_TO_POINT(65), PDF_BLACK); 
}