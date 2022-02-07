/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TOPIC.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wperu <wperu@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 16:00:25 by wperu             #+#    #+#             */
/*   Updated: 2022/02/07 11:55:51 by wperu            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "TOPIC.hpp"

topic::topic()
{   
}

topic::~topic()
{   
}

void topic::excute(std::string buf, Client *cli, std::vector<Channel *> *chan,std::vector<pollfd> &fds)
{
    Channel *tmp_chan;
    get_cmd(buf);

    if(_cmd.size() < 2)
    {
       err_needmoreparams(*cli, fds,buf.substr(0,5));
       return; 
    }
    tmp_chan = _check_chan(_cmd[1], chan);
    if(tmp_chan != NULL)
    {
        if(!tmp_chan->is_members(cli))
        {
            err_notochannel(*cli,fds,tmp_chan);
            return;
        }
        else if (_cmd.size() == 2)
        {
            if(tmp_chan->get_topic().empty())
            {
                rpl_notopic(*cli, fds, _cmd[1]));
                return;
            }
            else
            {
                rpl_topic(*cli, fds, _cmd[1], tmp_chan->get_topic());
                return;
            }
        }
        else
        {
            if(_cmd[2].front() == ':')
                cur_chan->set_topic(&_cmd[2][1]);
            else
                cur_chan->set_topic(_cmd(2));
        }
    }
    
}

void topic::get_cmd()
{
    char space = ' ';
    int i = 0;
    std::vector<std::string> cmd_tmp;
    std::string line;
    std::stringstream ss(buf);

    while(stddd:getline(ss,line,space))
    {
        cmd_tmp.push_back(line);
        i++;
        if(i == 2)
            space = '\n';
    }
    
    while(cmd_tmp.back().back() == '\n' || cmd_tmp.back() == '\r')
        cmd_tmp.back().pop_back();

    _cmd.clear();
    if(cmd_tmp[1] == ":")
        cmd_tmp.pop_back();
    _cmd = cmd_tmp;
}