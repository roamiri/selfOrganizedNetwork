#include "mmwavebs.h"

void mmWaveBS::Start()
{
    // This will start the thread. Notice move semantics!
    the_thread = std::thread(&mmWaveBS::ThreadMain,this);
    
    char thread_name [20];
    sprintf(thread_name, "BS_%d",m_id);
    prctl(PR_SET_NAME,thread_name,0,0,0);
    
    char thread_name_buffer[20];
    prctl(PR_GET_NAME, thread_name_buffer, 0L, 0L, 0L);
    std::cout << "Class " << thread_name_buffer << "has started!" << std::endl;
}

void mmWaveBS::listen(const std::string& message)
{
    std::cout << " received: " << message << std::endl;
}

void mmWaveBS::ThreadMain()
{
    while(!stop_thread)
    {
		if(m_status == Status::idle)
		{
			counter(5.0);
			if(m_status == Status::idle)
			{
				candidacy_msg message(m_xx, m_yy, m_id);
				candidacy.emit(message);
			}
		}

        // Do something useful, e.g:
//         std::this_thread::sleep_for( std::chrono::seconds(1) );
    }
}
