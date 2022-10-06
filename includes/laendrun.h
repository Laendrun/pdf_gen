#ifndef LAENDRUN_H
# define LAENDRUN_H
# include "libft.h"
# include "cJSON.h"
# include "pdfgen.h"
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <limits.h>
# include <stdbool.h>

// Margins + Offsets define
# define LEFT_MARGIN PDF_MM_TO_POINT(18)
# define ART_NO_XOFF PDF_MM_TO_POINT(18)
# define DESC_XOFF PDF_MM_TO_POINT(48)
# define QTY_XOFF PDF_MM_TO_POINT(115)
# define UNIT_PRICE_XOFF PDF_MM_TO_POINT(138)
# define AMOUNT_XOFF PDF_MM_TO_POINT(175)
# define TOTAL_XOFF PDF_MM_TO_POINT(115)

# define MAXCHAR 500

typedef struct s_document
{
  int type;
  char  *number;
  char  *client;

} t_document;

typedef struct s_cust
{
  char *cust_no;
  char *name;
  char *name2;
  char *adr;
  char *adr2;
  char *city;
  char *npa;
} t_cust;

typedef struct s_config
{
  char *logo_path;
  char *twint_qr_path;
  char *twint_dir_path;
} t_config;

// check.c
int		ft_char_is_num(char c);
int		ft_str_is_num(char *str);
int		ft_check_client_format(char *str);

// Document generations
// gen_fa.c
void gen_fa(t_document document, t_config config);
// gen_oc.c
void gen_oc(t_document document, t_config config);
// gen_cv.c
void gen_cv(t_document document, t_config config);

// helper.c
void pdf_add_header(struct pdf_doc *pdf, char *logo_path);
int pdf_add_dest_adr(struct pdf_doc *pdf, int mm, char *cust_no, char *name, char *name2, char *adr, char *adr2, char *city, char *npa);
void pdf_add_lines_header(struct pdf_doc *pdf, int mm);
void pdf_add_doc_no(struct pdf_doc *pdf, int mm, char *doc_type, char *doc_no);
void pdf_add_total_line(struct pdf_doc *pdf, float f_total_amount, int mm);
void pdf_add_invoice_page(struct pdf_doc *pdf, float f_total_amount, char *twint_qr_path, char *twint_dir_path, char *logo_path);

// errors.c
void	error(char *str);

#endif
