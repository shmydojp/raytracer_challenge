#ifndef _CANVAS_H
#define _CANVAS_H

#include <string>
#include <iostream>
#include <algorithm>
#include <fstream>

#include "color.h"

namespace Mido{
    class Canvas{
    public:
        explicit Canvas(int w, int h)
        : m_width{w}, m_height{h}, m_canvas{new Color*[m_width]}
        {
            for(int col = 0; col < m_width; ++col){
                m_canvas[col] = new Color[m_height];
            }
        }

        Color& operator()(int x, int y){
            assert(((x <= m_width - 1) && x >= 0)
                && "(Canvas::write_pixel): x value is out of bounds");
            assert(((y <= m_height - 1) && y >= 0)
                && "(Canvas::write_pixel): y value is out of bounds");
            return m_canvas[x][y];
        }

        void to_ppm(){
            using std::string, std::to_string, std::ofstream;

            ofstream ofs(PPM_FILE_NAME);
            if(!ofs){
                std::cerr << "Failed to open PPM_FILE_NAME for writing\n";
                return;
            }

            // creates the header first
            string ppm_header = "P3\n"
                            +   to_string(m_width) + ' ' + to_string(m_height)
                            +   "\n255\n";

            string ppm_data = string();
            string ppm_line = string();
            for(int row = 0; row < m_height; ++row){
                for(int col = 0; col < m_width; ++col){
                    const Color& c = m_canvas[col][row];
                    int r = static_cast<int>(
                                std::clamp(c.get_R(), 0.0, 1.0) * PPM_SCALE);
                    int g = static_cast<int>(
                                std::clamp(c.get_G(), 0.0, 1.0) * PPM_SCALE);
                    int b = static_cast<int>(
                                std::clamp(c.get_B(), 0.0, 1.0) * PPM_SCALE);

                    string pix_data = to_string(r) + ' '
                                    + to_string(g) + ' '
                                    + to_string(b);

                    size_t p_len = ppm_line.length();
                    size_t pix_len = pix_data.length();

                    if(p_len + pix_len + 1 < PPM_WIDTH){
                        ppm_line += pix_data + ' ';
                    }
                    else if(p_len + pix_len + 1 == PPM_WIDTH){
                        ppm_line += pix_data + '\n';
                        ppm_data += ppm_line;
                        ppm_line = string();
                    }
                    else{
                        char& ch_ref = ppm_line.back();
                        ch_ref = '\n';
                        ppm_data += ppm_line;
                        ppm_line = pix_data + ' ';
                    }
                }
                if(!ppm_line.empty()){
                    char& ch_ref = ppm_line.back();
                    ch_ref = '\n';
                    ppm_data += ppm_line;
                    ppm_line = string();
                }
            }
            // writes ppm to file
            ofs.write(
                &((ppm_header+ppm_data)[0]),
                ppm_header.size() + ppm_data.size());
        }

        inline int getWidth() const{
            return m_width;
        }

        inline int getHeight() const{
            return m_height;
        }

    private:
        int m_width;
        int m_height;
        Color** m_canvas;

        static constexpr int PPM_WIDTH = 70;
        static constexpr int PPM_SCALE  = 255;

        inline static const char* PPM_FILE_NAME = "output.ppm";
    };
}

#endif
