#include "laendrun.h"

void gen_oc(t_document document, t_config config)
{
  FILE *customers;
  FILE *sales_lines;
  t_cust cust;
  char row[MAXCHAR];
  char * art_no, * desc, * qty, * unit, * unit_price;
  float f_total_amount;
  int total_pages = 0;
  int mm = 235;
  struct pdf_object *pages[100];

  customers = fopen("./customers.csv","r");
  if (customers == NULL){
    printf("cannot open customers\n");
    exit(1);
  }

    while (feof(customers) != true)
    {
      fgets(row, MAXCHAR, customers);
      char customers[10][50];
      int i,j,ctr;

      j=0; ctr=0;
      for(i=0;i<=((int)strlen(row));i++)
      {
        // if space or NULL found, assign NULL into newString[ctr]
        if(row[i]==','||row[i]=='\0')
        {
          customers[ctr][j]='\0';
          ctr++;  //for next word
          j=0;    //for next word, init index to 0
        }
        else
        {
          customers[ctr][j]=row[i];
          j++;
        }
      } //for
      if(strcmp(document.client, customers[0]) == 0){
        cust.cust_no = customers[0];
        cust.name = customers[1];
        cust.name2 = customers[2];
        cust.adr = customers[3];
        cust.adr2 = customers[4];
        cust.npa = customers[5];
        cust.city = customers[6];
      } //if
    } //while

  struct pdf_info info = {
          .creator = "Simon Aeby",
          .producer = "",
          .title = "",
          .author = "Simon Aeby",
          .subject = "",
          .date = "Today"
  };
  struct pdf_doc *pdf = pdf_create(PDF_A4_WIDTH, PDF_A4_HEIGHT, &info);
  pdf_set_font(pdf, "Courier");
  pages[total_pages] = pdf_append_page(pdf);

  pdf_add_header(pdf, config.logo_path);

  mm = pdf_add_dest_adr(pdf, mm, cust.cust_no, cust.name, cust.name2, cust.adr, cust.adr2, cust.city, cust.npa);
  pdf_add_doc_no(pdf, mm, "OC", document.number);

  mm = mm-20;
  pdf_add_lines_header(pdf, mm);
  mm = mm-8;

  sales_lines = fopen("./sales_lines.csv","r");
  if (sales_lines == NULL){
    printf("cannot open sales lines\n");
    exit(1);
  }

  while (feof(sales_lines) != true)
  {
    fgets(row, MAXCHAR, sales_lines);
    char sales_line[10][50];
    int i,j,ctr;

    j=0; ctr=0;
    for(i=0;i<=((int)strlen(row));i++)
    {
      // if space or NULL found, assign NULL into newString[ctr]
      if(row[i]==','||row[i]=='\0')
      {
        sales_line[ctr][j]='\0';
        ctr++;  //for next word
        j=0;    //for next word, init index to 0
      }
      else
      {
        sales_line[ctr][j]=row[i];
        j++;
      }

    }
    art_no = sales_line[0];
    desc = sales_line[1];
    qty = sales_line[2];
    unit = sales_line[3];
    unit_price = sales_line[4];
    strcat(qty, " ");
    strcat(qty, unit);
    float quantity = atof(qty);
    float price = atof(unit_price);
    float f_amount = quantity * price;
    f_total_amount = f_total_amount + f_amount;
    char c_amount[50];
    gcvt(f_amount, 6, c_amount);
    pdf_add_text(pdf, NULL, art_no, 12, ART_NO_XOFF, PDF_MM_TO_POINT(mm), PDF_BLACK);
    pdf_add_text(pdf, NULL, desc, 12, DESC_XOFF, PDF_MM_TO_POINT(mm), PDF_BLACK);
    pdf_add_text(pdf, NULL, qty, 12, QTY_XOFF, PDF_MM_TO_POINT(mm), PDF_BLACK);
    pdf_add_text(pdf, NULL, unit_price, 12, UNIT_PRICE_XOFF, PDF_MM_TO_POINT(mm), PDF_BLACK);
    pdf_add_text(pdf, NULL, c_amount, 12, AMOUNT_XOFF, PDF_MM_TO_POINT(mm), PDF_BLACK);
    mm = mm-7;
    if(mm <= 45){
      char c_total_amount[75]="";
      gcvt(f_total_amount, 6, c_total_amount);
      pdf_add_text(pdf, NULL, "Sous-total : ", 12, TOTAL_XOFF, PDF_MM_TO_POINT(35), PDF_BLACK);
      pdf_add_text(pdf, NULL, c_total_amount, 12, AMOUNT_XOFF, PDF_MM_TO_POINT(35), PDF_BLACK);
      pdf_add_line(pdf, NULL, PDF_MM_TO_POINT(172), PDF_MM_TO_POINT(33), PDF_MM_TO_POINT(192), PDF_MM_TO_POINT(33), 0.5, PDF_BLACK);
      total_pages++;
      pages[total_pages] = pdf_append_page(pdf);
      pdf_add_header(pdf, config.logo_path);
      pdf_add_lines_header(pdf, 235);
      mm = 228;
    }
  }

  pdf_add_total_line(pdf, f_total_amount, mm);

  for (int i=0; i<=total_pages; i++){
    char page_txt[25] = "Page ";
    char tmp[25];
    sprintf(tmp, "%d", i+1);
    strcat(page_txt, tmp);
    strcat(page_txt, "/");
    sprintf(tmp, "%d", total_pages+1);
    strcat(page_txt, tmp);
    //strcat(tmp, j);
    pdf_add_text(pdf, pages[i], page_txt, 12, PDF_MM_TO_POINT(160), PDF_MM_TO_POINT(250), PDF_BLACK);
  }
  char output_path[50];
  strcat(output_path, "./offres/OC");
  strcat(output_path, document.number);
  strcat(output_path, ".pdf");
  pdf_save(pdf, output_path);
  pdf_destroy(pdf);
}