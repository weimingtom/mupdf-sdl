#if defined(__MINGW32__)

#include "pdfapp.h"

static pdfapp_t gapp;



void winwarn(pdfapp_t *app, char *msg)
{

}

void winerror(pdfapp_t *app, char *msg)
{
	exit(1);
}

void winalert(pdfapp_t *app, pdf_alert_event *alert)
{

}

//----------
//winprint
void winprint(pdfapp_t *app)
{

}

int winsavequery(pdfapp_t *app)
{
//return SAVE;
//return DISCARD;
//return CANCEL;
	return CANCEL;
}

int wingetsavepath(pdfapp_t *app, char *buf, int len)
{
	return 0;
}

void winreplacefile(char *source, char *target)
{

}

void wincopyfile(char *source, char *target)
{

}

char *winpassword(pdfapp_t *app, char *filename)
{
	return NULL;
}

char *wintextinput(pdfapp_t *app, char *inittext, int retry)
{
	return NULL;
}

int winchoiceinput(pdfapp_t *app, int nopts, char *opts[], int *nvals, char *vals[])
{
	return 0;
}

void winhelp(pdfapp_t *app)
{
}

void winclose(pdfapp_t *app)
{
	if (pdfapp_preclose(app))
	{

		exit(0);
	}
}

void wincursor(pdfapp_t *app, int curs)
{
}

void wintitle(pdfapp_t *app, char *title)
{
}



void windrawstring(pdfapp_t *app, int x, int y, char *s)
{
}

void winresize(pdfapp_t *app, int w, int h)
{
}

void winrepaint(pdfapp_t *app)
{
}

void winrepaintsearch(pdfapp_t *app)
{
}

void winfullscreen(pdfapp_t *app, int state)
{
}



void windocopy(pdfapp_t *app)
{
}

void winreloadpage(pdfapp_t *app)
{
}

void winopenuri(pdfapp_t *app, char *buf)
{
}




//----------
//winadvancetimer
void winadvancetimer(pdfapp_t *app, float duration)
{
}

static void usage(void)
{
	fprintf(stderr, "usage: mupdf [options] file.pdf [page]\n");
	fprintf(stderr, "\t-p -\tpassword\n");
	fprintf(stderr, "\t-r -\tresolution\n");
	fprintf(stderr, "\t-A -\tset anti-aliasing quality in bits (0=off, 8=best)\n");
	fprintf(stderr, "\t-C -\tRRGGBB (tint color in hexadecimal syntax)\n");
	fprintf(stderr, "\t-W -\tpage width for EPUB layout\n");
	fprintf(stderr, "\t-H -\tpage height for EPUB layout\n");
	fprintf(stderr, "\t-S -\tfont size for EPUB layout\n");
	fprintf(stderr, "\t-U -\tuser style sheet for EPUB layout\n");
	exit(1);
}

int main(int argc, char *argv[])
{
	return 0;
}


#endif
