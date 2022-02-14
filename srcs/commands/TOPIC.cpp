/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TOPIC.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wperu <wperu@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 16:00:25 by wperu             #+#    #+#             */
/*   Updated: 2022/02/14 17:15:45 by wperu            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "commands/TOPIC.hpp"

topic::topic()
{   
}

topic::~topic()
{   
}

void topic::excute(std::string buf, Client *cli, std::vector<Channel > *chan,std::vector<pollfd> &fds)
{
    Channel *tmp_chan;
    std::string tmp_buf;
    pars_msg(buf,tmp_buf,_cmd);
    std::cout<<_cmd.size()<<std::endl;
    if(_cmd.size() < 1)
    {
       err_needmoreparams(*cli, fds,buf.substr(0,5));
       return; 
    }
    tmp_chan = _check_chan(_cmd[0], chan);
    
    if(tmp_chan != NULL)
    {
        if(!tmp_chan->is_members(cli->get_nickname()))
        {
            err_notochannel(*cli,fds,_cmd[1]);
            return;
        }
        else if (_cmd.size() == 1)
        {
            if(tmp_chan->get_topic().empty())
            {
                rpl_notopic(*cli, fds, _cmd[0]);
                return;
            }
            else
            {
                rpl_topic(*cli, fds, _cmd[0], tmp_chan->get_topic());
                return;
            }
        }
        else
        {
            if(_cmd[2].front() == ':')
                tmp_chan->set_topic(&_cmd[1][1]);
            else
                tmp_chan->set_topic(_cmd[1]);
        }
    }
    
}
/*
void topic::get_cmd(std::string buf)
{
    char space = ' ';
    int i = 0;
    std::vector<std::string> cmd_tmp;
    std::string line;
    std::stringstream ss(buf);
    std::cout<<buf+"|"<<std::endl;
    while(std::getline(ss,line,space))
    {
        std::cout<<line<<std::endl;
        cmd_tmp.push_back(line);
        i++;
        if(i == 2)
            space = '\n';
    }
    std::cout<<cmd_tmp[0]<<std::endl;
    while(cmd_tmp.back().back() == '\n' || cmd_tmp.back() == "\r")
        cmd_tmp.back().pop_back();

    _cmd.clear();
    if(cmd_tmp[1] == ":")
        cmd_tmp.pop_back();
    _cmd = cmd_tmp;
}*/