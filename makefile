.PHONY : clean

T = './common'

CODE1 = wechat.c $(T)/common.c $(T)/Udp_server.c $(T)/Udp_client.c $(T)/reactor.c $(T)/client_discover.c

CODE2 = $(T)/heart_beat.c $(T)/send_chat.c $(T)/chat_ui.c

all :
	gcc $(CODE1) $(CODE2) -I $(T) -o wechat.out -l pthread -l ncurses
clean : 
	rm ./wechat.out
