
#  Copyright (C) 2019 Anthony Buckley
# 
#  This file is part of CairoChart.
# 
#  CairoChart is free software: you can redistribute it and/or modify
#  it under the terms of the GNU General Public License as published by
#  the Free Software Foundation, either version 3 of the License, or
#  (at your option) any later version.
# 
#  CairoChart is distributed in the hope that it will be useful,
#  but WITHOUT ANY WARRANTY; without even the implied warranty of
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#  GNU General Public License for more details.
# 
#  You should have received a copy of the GNU General Public License
#  along with CairoChart.  If not, see <http://www.gnu.org/licenses/>.

CC=cc
FW=../framework
CFLAGS=-I. `pkg-config --cflags gtk+-3.0` 
CFLAGS2=-Wno-deprecated-declarations
DEPS = demo.h $(FW)/cairo_chart.h
OBJ = demo_main.o demo_main_ui.o demo_css.o $(FW)/cairo_chart_cb.o $(FW)/cairo_chart.o
LIBS = `pkg-config --libs gtk+-3.0 cairo`
LIBS2 = -lm

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS) $(CFLAGS2)

cairochart: $(OBJ)
	$(CC) -o $@ $^ $(LIBS) $(LIBS2)

clean:
	rm -f $(OBJ)
