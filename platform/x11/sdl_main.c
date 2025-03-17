// make -f Makefile.mingw
// make -f Makefile.mingw test

#include "pdfapp.h"

#ifdef __MINGW32__
#include <SDL.h>
#else
#include <SDL/SDL.h>
#endif
#include <stdio.h>
#ifdef __MINGW32__
//skip
#else
#include <sys/select.h>
#include <sys/wait.h>
#endif
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480
#define WIN_BPP 32
//#define WINDOW_BGCOLOR 0x000000 
#define WINDOW_BGCOLOR 0xCCCCCC

static SDL_Surface *s_screen;
static SDL_Rect s_screenArea;

void cleanup(pdfapp_t *app);

static int dirty = 0;
static int transition_dirty = 0;
static int dirtysearch = 0;
static char *password = "";
static char *filename;

static pdfapp_t gapp;
static int closing = 0;
static int reloading = 0;
static int showingpage = 0;
static int showingmessage = 0;

static int advance_scheduled = 0;
static struct timeval tmo;
static struct timeval tmo_advance;
static struct timeval tmo_at;


void winwarn(pdfapp_t *app, char *msg)
{
	fprintf(stderr, "warning: %s\n", msg);
}

void winerror(pdfapp_t *app, char *msg)
{
	fprintf(stderr, "mupdf: error: %s\n", msg);
	cleanup(app);
	exit(1);
}

void winalert(pdfapp_t *app, pdf_alert_event *alert)
{
	fprintf(stderr, "Alert %s: %s\n", alert->title, alert->message);
	switch (alert->button_group_type)
	{
	case PDF_ALERT_BUTTON_GROUP_OK:
	case PDF_ALERT_BUTTON_GROUP_OK_CANCEL:
		alert->button_pressed = PDF_ALERT_BUTTON_OK;
		break;
	case PDF_ALERT_BUTTON_GROUP_YES_NO:
	case PDF_ALERT_BUTTON_GROUP_YES_NO_CANCEL:
		alert->button_pressed = PDF_ALERT_BUTTON_YES;
		break;
	}
}

//----------
//winprint
void winprint(pdfapp_t *app)
{
	fprintf(stderr, "The MuPDF library supports printing, but this application currently does not\n");
}







/*
 * SDL open
 */

static void winopen(void)
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		fprintf(stderr, "Couldn't initialize SDL: %s\n", SDL_GetError());
		exit(1);
	}
	s_screen = SDL_SetVideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, WIN_BPP, SDL_SWSURFACE);
	if (s_screen == NULL) 
	{
		fprintf(stderr, "Couldn't set display mode: %s\n", SDL_GetError());
		exit(1);
	}
	static SDL_Rect area = {0, 0, WINDOW_WIDTH, WINDOW_HEIGHT};
	if (SDL_MUSTLOCK(s_screen))
	{
		if (SDL_LockSurface(s_screen) < 0)
		{
			fprintf(stderr, "Couldn't lock display surface: %s\n", SDL_GetError());
			exit(1);
		}
	}
	SDL_FillRect(s_screen, &area, 
		SDL_MapRGB(s_screen->format, 
		(Uint8)WINDOW_BGCOLOR, 
		(Uint8)(WINDOW_BGCOLOR >> 8), 
		(Uint8)(WINDOW_BGCOLOR >> 16)));
	if (SDL_MUSTLOCK(s_screen))
	{
		SDL_UnlockSurface(s_screen);
	}
	SDL_UpdateRect(s_screen, 0, 0, 0, 0);
}

//----------
//winsavequery
int winsavequery(pdfapp_t *app)
{
	fprintf(stderr, "mupdf: discarded changes to document\n");
	/* FIXME: temporary dummy implementation */
	return DISCARD;
}

int wingetsavepath(pdfapp_t *app, char *buf, int len)
{
	/* FIXME: temporary dummy implementation */
	return 0;
}

void winreplacefile(char *source, char *target)
{
	rename(source, target);
}

void wincopyfile(char *source, char *target)
{
	char *buf = malloc(strlen(source)+strlen(target)+5);
	if (buf)
	{
		sprintf(buf, "cp %s %s", source, target);
		system(buf);
		free(buf);
	}
}

char *winpassword(pdfapp_t *app, char *filename)
{
	char *r = password;
	password = NULL;
	return r;
}

char *wintextinput(pdfapp_t *app, char *inittext, int retry)
{
	static char buf[256];

	if (retry)
		return NULL;

	printf("> [%s] ", inittext);
	fgets(buf, sizeof buf, stdin);
	return buf;
}

void cleanup(pdfapp_t *app)
{
	fz_context *ctx = app->ctx;

	pdfapp_close(app);

	//XDestroyWindow(xdpy, xwin);

	//XFreePixmap(xdpy, xicon);

	//XFreeCursor(xdpy, xccaret);
	//XFreeCursor(xdpy, xcwait);
	//XFreeCursor(xdpy, xchand);
	//XFreeCursor(xdpy, xcarrow);

	//XFreeGC(xdpy, xgc);

	//XCloseDisplay(xdpy);

	SDL_FreeSurface(s_screen);
	s_screen = NULL;
	SDL_Quit();

	fz_drop_context(ctx);
}

static int winresolution()
{
	//return DisplayWidth(xdpy, xscr) * 25.4 /
	//	DisplayWidthMM(xdpy, xscr) + 0.5;
	return 96;//96dpi
}

int winchoiceinput(pdfapp_t *app, int nopts, char *opts[], int *nvals, char *vals[])
{
	/* FIXME: temporary dummy implementation */
	return 0;
}

void winhelp(pdfapp_t *app)
{
	fprintf(stderr, "%s\n%s", pdfapp_version(app), pdfapp_usage(app));
}

static void winblitstatusbar(pdfapp_t *app)
{
//TODO:
}

int g_time = 0;
static void winblit(pdfapp_t *app)
{
#if 0	
	SDL_Rect rAll = {0, 0, 640, 480};
	SDL_FillRect(s_screen, NULL, //&rAll, 
		SDL_MapRGB(s_screen->format, 
		(Uint8)WINDOW_BGCOLOR, 
		(Uint8)(WINDOW_BGCOLOR >> 8), 
		(Uint8)(WINDOW_BGCOLOR >> 16)));
#endif
	
//TODO:
	int image_w = fz_pixmap_width(gapp.ctx, gapp.image);
	int image_h = fz_pixmap_height(gapp.ctx, gapp.image);
	int image_n = fz_pixmap_components(gapp.ctx, gapp.image);
	unsigned char *samples = fz_pixmap_samples(gapp.ctx, gapp.image);
	int x0 = gapp.panx;
	int y0 = gapp.pany;
	int x1 = gapp.panx + image_w;
	int y1 = gapp.pany + image_h;
	SDL_Rect r;
	
	if (gapp.image)
	{
#if 0		
		if (gapp.iscopying || justcopied)
		{
			pdfapp_invert(&gapp, &gapp.selr);
			justcopied = 1;
		}
#endif

		pdfapp_inverthit(&gapp);

#if 0		
		dibinf->bmiHeader.biWidth = image_w;
		dibinf->bmiHeader.biHeight = -image_h;
		dibinf->bmiHeader.biSizeImage = image_h * 4;
#else
	

#define Rmask 0x000000FF
#define Gmask 0x0000FF00
#define Bmask 0x00FF0000
#define Amask 0xFF000000
		fprintf(stderr, ">>>>>winblit(%d) %d, %d\n", g_time++, image_w, image_h);
		SDL_Surface *dibinf = SDL_CreateRGBSurface(0,
			image_w, image_h, 32,
			Rmask, Gmask, Bmask, Amask
		);
#endif
		if (image_n == 2)
		{
			int i = image_w * image_h;
			unsigned char *color = malloc(i*4);
			unsigned char *s = samples;
			unsigned char *d = color;
			for (; i > 0 ; i--)
			{
				d[2] = d[1] = d[0] = *s++;
				d[3] = *s++;
				d += 4;
			}
#if 0		
			SetDIBitsToDevice(hdc,
				gapp.panx, gapp.pany, image_w, image_h,
				0, 0, 0, image_h, color,
				dibinf, DIB_RGB_COLORS);
#else
			SDL_LockSurface(dibinf);
			//screen->pixels, screen->w, screen->h
			SDL_memcpy(dibinf->pixels, color, image_w * image_h * 4);
			SDL_UnlockSurface(dibinf);
			SDL_Rect dstRect = {gapp.panx, gapp.pany, image_w, image_h};
			SDL_Rect srcRect = {0, 0, image_w, image_h};
			SDL_BlitSurface(dibinf, &srcRect, s_screen, &dstRect);
#endif	
			free(color);
		}
		if (image_n == 4)
		{
#if 0			
			SetDIBitsToDevice(hdc,
				gapp.panx, gapp.pany, image_w, image_h,
				0, 0, 0, image_h, samples,
				dibinf, DIB_RGB_COLORS);
#else
			SDL_LockSurface(dibinf);
			//screen->pixels, screen->w, screen->h
			SDL_memcpy(dibinf->pixels, samples, image_w * image_h * 4);
			SDL_UnlockSurface(dibinf);
			SDL_Rect dstRect = {gapp.panx, gapp.pany, image_w, image_h};
			SDL_Rect srcRect = {0, 0, image_w, image_h};
			SDL_BlitSurface(dibinf, &srcRect, s_screen, &dstRect);
#endif					
		}
		if (dibinf) {
			SDL_FreeSurface(dibinf);
		}
		
		pdfapp_inverthit(&gapp);

#if 0		
		if (gapp.iscopying || justcopied)
		{
			pdfapp_invert(&gapp, &gapp.selr);
			justcopied = 1;
		}
#endif		
	}
	
	
	
	
	
	
	
	
	
	
	
	
	
#define USE_FILL 0	
#if USE_FILL //TODO: don't know how to fill	


//#define WINDOW_BGCOLOR 0xCCCCCC
	
	/* Grey background */
	r.y = 0; r.h = gapp.winh;
	r.x = 0; r.w = x0;
#if 0	
	FillRect(hdc, &r, bgbrush);
#else
	SDL_FillRect(s_screen, &r, 
		SDL_MapRGB(s_screen->format, 
		(Uint8)WINDOW_BGCOLOR, 
		(Uint8)(WINDOW_BGCOLOR >> 8), 
		(Uint8)(WINDOW_BGCOLOR >> 16)));
#endif	
	r.x = x1; r.w = gapp.winw - x1;
#if 0	
	FillRect(hdc, &r, bgbrush);
#else
	SDL_FillRect(s_screen, &r, 
		SDL_MapRGB(s_screen->format, 
		(Uint8)WINDOW_BGCOLOR, 
		(Uint8)(WINDOW_BGCOLOR >> 8), 
		(Uint8)(WINDOW_BGCOLOR >> 16)));
#endif	
	r.x = 0; r.w = gapp.winw - 0;
	r.y = 0; r.h = y0 - 0;
#if 0	
	FillRect(hdc, &r, bgbrush);
#else
	SDL_FillRect(s_screen, &r, 
		SDL_MapRGB(s_screen->format, 
		(Uint8)WINDOW_BGCOLOR, 
		(Uint8)(WINDOW_BGCOLOR >> 8), 
		(Uint8)(WINDOW_BGCOLOR >> 16)));
#endif	
	r.y = y1; r.h = gapp.winh - y1;
#if 0	
	FillRect(hdc, &r, bgbrush);
#else
	SDL_FillRect(s_screen, &r, 
		SDL_MapRGB(s_screen->format, 
		(Uint8)WINDOW_BGCOLOR, 
		(Uint8)(WINDOW_BGCOLOR >> 8), 
		(Uint8)(WINDOW_BGCOLOR >> 16)));
#endif	

	/* Drop shadow */
	r.x = x0 + 2;
	r.w = x1 + 2 - (x0 + 2);
	r.y = y1;
	r.h = y1 + 2 - y1;
#if 0	
	FillRect(hdc, &r, shbrush);
#else
	SDL_FillRect(s_screen, &r, 
		SDL_MapRGB(s_screen->format, 
		(Uint8)WINDOW_BGCOLOR, 
		(Uint8)(WINDOW_BGCOLOR >> 8), 
		(Uint8)(WINDOW_BGCOLOR >> 16)));
#endif	
	r.x = x1;
	r.w = x1 + 2 - x1;
	r.y = y0 + 2;
	r.h = y1 - (y0 + 2);
#if 0
	FillRect(hdc, &r, shbrush);
#else
	SDL_FillRect(s_screen, &r, 
		SDL_MapRGB(s_screen->format, 
		(Uint8)WINDOW_BGCOLOR, 
		(Uint8)(WINDOW_BGCOLOR >> 8), 
		(Uint8)(WINDOW_BGCOLOR >> 16)));
#endif



#endif //if USE_FILL


	SDL_UpdateRect(s_screen, 0, 0, 0, 0);

	//winblitsearch();
}


void winclose(pdfapp_t *app)
{
	if (pdfapp_preclose(app))
	{
		closing = 1;
		exit(0);
	}
}

void wincursor(pdfapp_t *app, int curs)
{
//TODO: change mouse cursor
}

void wintitle(pdfapp_t *app, char *title)
{
//TODO: change window title
	SDL_WM_SetCaption(title, NULL);
}

void windrawstring(pdfapp_t *app, int x, int y, char *s)
{
//TODO: draw text
}

void winresize(pdfapp_t *app, int w, int h)
{
//TODO: resize window
}

void winrepaint(pdfapp_t *app)
{
//FIXME:
	dirty = 1;
	if (app->in_transit)
		transition_dirty = 1;
	SDL_UpdateRects(s_screen, 1, &s_screenArea);
}

void winrepaintsearch(pdfapp_t *app)
{
//FIXME:
	dirtysearch = 1;
	SDL_UpdateRects(s_screen, 1, &s_screenArea);
}

void winfullscreen(pdfapp_t *app, int state)
{
}



void windocopy(pdfapp_t *app)
{
//TODO:
}

void winreloadpage(pdfapp_t *app)
{
//TODO:
}

void winopenuri(pdfapp_t *app, char *buf)
{
//TODO:
}

static void onkey(int c, int modifiers)
{
	advance_scheduled = 0;

#if 0	
	if (justcopied)
	{
		justcopied = 0;
		winrepaint(&gapp);
	}
	
	if (!gapp.issearching && c == 'P')
	{
		struct timeval now;
		struct timeval tmo;
		tmo.tv_sec = 2;
		tmo.tv_usec = 0;
		gettimeofday(&now, NULL);
		timeradd(&now, &tmo, &tmo_at);
		showingpage = 1;
		winrepaint(&gapp);
		return;
	}
#endif

	pdfapp_onkey(&gapp, c, modifiers);

	if (gapp.issearching)
	{
		showingpage = 0;
		showingmessage = 0;
	}
}

static void onmouse(int x, int y, int btn, int modifiers, int state)
{
	if (state != 0)
		advance_scheduled = 0;

#if  0	
	if (state != 0 && justcopied)
	{
		justcopied = 0;
		winrepaint(&gapp);
	}
#endif	

	pdfapp_onmouse(&gapp, x, y, btn, modifiers, state);
}

static void signal_handler(int signal)
{
#ifndef __MINGW32__	
	if (signal == SIGHUP)
		reloading = 1;
#endif
}

//----------
//winadvancetimer
void winadvancetimer(pdfapp_t *app, float duration)
{
#ifndef __MINGW32__	
	struct timeval now;

	gettimeofday(&now, NULL);
	memset(&tmo_advance, 0, sizeof(tmo_advance));
	tmo_advance.tv_sec = (int)duration;
	tmo_advance.tv_usec = 1000000 * (duration - tmo_advance.tv_sec);
	timeradd(&tmo_advance, &now, &tmo_advance);
	advance_scheduled = 1;
#endif
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
	int c;
	int len;
	char buf[128];

	int oldx = 0;
	int oldy = 0;
	int resolution = -1;
	int pageno = 1;
#ifndef __MINGW32__		
	fd_set fds;
#endif	
	int width = -1;
	int height = -1;
	fz_context *ctx;
	struct timeval now;
	struct timeval *timeout;
	struct timeval tmo_advance_delay;
	SDL_Event event;

	ctx = fz_new_context(NULL, NULL, FZ_STORE_DEFAULT);
	if (!ctx)
	{
		fprintf(stderr, "cannot initialise context\n");
		exit(1);
	}

	pdfapp_init(ctx, &gapp);

	while ((c = fz_getopt(argc, argv, "p:r:A:C:W:H:S:U:")) != -1)
	{
		switch (c)
		{
		case 'C':
			c = strtol(fz_optarg, NULL, 16);
			gapp.tint = 1;
			gapp.tint_r = (c >> 16) & 255;
			gapp.tint_g = (c >> 8) & 255;
			gapp.tint_b = (c) & 255;
			break;
		case 'p': password = fz_optarg; break;
		case 'r': resolution = atoi(fz_optarg); break;
		case 'A': fz_set_aa_level(ctx, atoi(fz_optarg)); break;
		case 'W': gapp.layout_w = fz_atof(fz_optarg); break;
		case 'H': gapp.layout_h = fz_atof(fz_optarg); break;
		case 'S': gapp.layout_em = fz_atof(fz_optarg); break;
		case 'U': gapp.layout_css = fz_optarg; break;
		default: usage();
		}
	}

	if (argc - fz_optind == 0)
		usage();

	filename = argv[fz_optind++];

	if (argc - fz_optind == 1)
		pageno = atoi(argv[fz_optind++]);

	winopen();

	if (resolution == -1)
		resolution = winresolution();
	if (resolution < MINRES)
		resolution = MINRES;
	if (resolution > MAXRES)
		resolution = MAXRES;

	gapp.transitions_enabled = 1;
	gapp.scrw = WINDOW_WIDTH;
	gapp.scrh = WINDOW_HEIGHT;
	gapp.resolution = resolution;
	gapp.pageno = pageno;

	tmo_at.tv_sec = 0;
	tmo_at.tv_usec = 0;
	timeout = NULL;

	pdfapp_open(&gapp, filename, 0);

#ifndef __MINGW32__		
	FD_ZERO(&fds);

	signal(SIGHUP, signal_handler);
#endif

#if 1
//FIXME: zoom for screen width, if width is not changed
pdfapp_onresize(&gapp, WINDOW_WIDTH, WINDOW_HEIGHT);
pdfapp_autozoom_horizontal(&gapp);
#endif

	while (!closing)
	{
		while (!closing && SDL_PollEvent(&event) && !transition_dirty)
		{
			//XNextEvent(xdpy, &xevt);

			switch (event.type)
			{
			case SDL_VIDEOEXPOSE:
				dirty = 1;
				break;

			case SDL_VIDEORESIZE:
				//if (gapp.image)
				//{
				//	if (xevt.xconfigure.width != reqw ||
				//		xevt.xconfigure.height != reqh)
				//		gapp.shrinkwrap = 0;
				//}
				//width = xevt.xconfigure.width;
				//height = xevt.xconfigure.height;
				//break;

			case SDL_KEYDOWN:
				//len = XLookupString(&xevt.xkey, buf, sizeof buf, &keysym, NULL);

				if (!gapp.issearching)
					switch (event.key.keysym.sym)
					{
					case SDLK_ESCAPE:
						len = 1; buf[0] = '\033';
						break;

					case SDLK_UP:
						len = 1; buf[0] = 'k';
						break;
					case SDLK_DOWN:
						len = 1; buf[0] = 'j';
						break;

					case SDLK_LEFT:
						len = 1; buf[0] = 'b';
						break;
					case SDLK_RIGHT:
						len = 1; buf[0] = ' ';
						break;

					case SDLK_PAGEUP:
					//case XF86XK_Back:
						len = 1; buf[0] = ',';
						break;
					case SDLK_PAGEDOWN:
					//case XF86XK_Forward:
						len = 1; buf[0] = '.';
						break;
					}
#if 0					
				if (xevt.xkey.state & ControlMask && keysym == XK_c)
					docopy(&gapp, XA_CLIPBOARD);
				else if (len)
					onkey(buf[0], xevt.xkey.state);
#else			
				if (len) {
					onkey(buf[0], 0);
				}
#endif
				
				onmouse(oldx, oldy, 0, 0, 0);
				break;

			case SDL_MOUSEMOTION:
				//oldx = xevt.xmotion.x;
				//oldy = xevt.xmotion.y;
				//onmouse(xevt.xmotion.x, xevt.xmotion.y, 0, xevt.xmotion.state, 0);
				break;

			case SDL_MOUSEBUTTONDOWN:
				//onmouse(xevt.xbutton.x, xevt.xbutton.y, xevt.xbutton.button, xevt.xbutton.state, 1);
				break;

			case SDL_MOUSEBUTTONUP:
				//copytime = xevt.xbutton.time;
				//onmouse(xevt.xbutton.x, xevt.xbutton.y, xevt.xbutton.button, xevt.xbutton.state, -1);
				break;

			//case SelectionRequest:
			//	onselreq(xevt.xselectionrequest.requestor,
			//		xevt.xselectionrequest.selection,
			//		xevt.xselectionrequest.target,
			//		xevt.xselectionrequest.property,
			//		xevt.xselectionrequest.time);
			//	break;

			//case ClientMessage:
			//	if (xevt.xclient.message_type == WM_RELOAD_PAGE)
			//		pdfapp_reloadpage(&gapp);
			//	else if (xevt.xclient.format == 32 && xevt.xclient.data.l[0] == WM_DELETE_WINDOW)
			//		closing = 1;
			//	break;


			case SDL_QUIT:
				closing = 1;
				break;
			}
		
			//FIXME:
			usleep((unsigned long)(1000));
		}

		if (closing)
			continue;

#if 0		
		if (width != -1 || height != -1)
		{
			pdfapp_onresize(&gapp, width, height);
			width = -1;
			height = -1;
		}
#else
		//FIXME:
		pdfapp_onresize(&gapp, WINDOW_WIDTH, WINDOW_HEIGHT);	
#endif	

		if (dirty || dirtysearch)
		{
			if (dirty)
				winblit(&gapp);
			else if (dirtysearch)
				winblitstatusbar(&gapp);
			dirty = 0;
			transition_dirty = 0;
			dirtysearch = 0;
			pdfapp_postblit(&gapp);
		}

		if (!showingpage && !showingmessage && (tmo_at.tv_sec || tmo_at.tv_usec))
		{
			tmo_at.tv_sec = 0;
			tmo_at.tv_usec = 0;
			timeout = NULL;
		}

		if (/*XPending(xdpy) ||*/ transition_dirty)
			continue;

		timeout = NULL;

#ifndef __MINGW32__		
		if (tmo_at.tv_sec || tmo_at.tv_usec)
		{
			gettimeofday(&now, NULL);
			timersub(&tmo_at, &now, &tmo);
			if (tmo.tv_sec <= 0)
			{
				tmo_at.tv_sec = 0;
				tmo_at.tv_usec = 0;
				timeout = NULL;
				showingpage = 0;
				showingmessage = 0;
				winrepaint(&gapp);
			}
			else
				timeout = &tmo;
		}

		if (advance_scheduled)
		{
			gettimeofday(&now, NULL);
			timersub(&tmo_advance, &now, &tmo_advance_delay);
			if (tmo_advance_delay.tv_sec <= 0)
			{
				/* Too late already */
				//onkey(' ', 0);
				//onmouse(oldx, oldy, 0, 0, 0);
				advance_scheduled = 0;
			}
			else if (timeout == NULL)
			{
				timeout = &tmo_advance_delay;
			}
			else
			{
				struct timeval tmp;
				timersub(&tmo_advance_delay, timeout, &tmp);
				if (tmp.tv_sec < 0)
				{
					timeout = &tmo_advance_delay;
				}
			}
		}
#endif

		//FD_SET(x11fd, &fds);
		//if (select(x11fd + 1, &fds, NULL, NULL, timeout) < 0)
		//{
		//	if (reloading)
		//	{
		//		pdfapp_reloadfile(&gapp);
		//		reloading = 0;
		//	}
		//}
		//if (!FD_ISSET(x11fd, &fds))
		//{
		//	if (timeout == &tmo_advance_delay)
		//	{
		//		onkey(' ', 0);
		//		onmouse(oldx, oldy, 0, 0, 0);
		//		advance_scheduled = 0;
		//	}
		//	else
		//	{
		//		tmo_at.tv_sec = 0;
		//		tmo_at.tv_usec = 0;
		//		timeout = NULL;
		//		showingpage = 0;
		//		showingmessage = 0;
		//		winrepaint(&gapp);
		//	}
		//}

		//FIXME:
		usleep((unsigned long)(1000));
	}

	cleanup(&gapp);

	return 0;
}


