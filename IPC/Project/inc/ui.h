#ifndef __UI_H__
#define __UI_H__

/** 
 * @brief
 * 
 * 
 * @author Author Shai Horesh (shihoresh@gmail.com)
 */ 

/**  
 * @brief  
 * @param[in] 
 * @param[out] 
 * @return 
 * @retval 
 * @warning
 */
int RetrieveSubscriber(char* _msisdn);

int RetrieveOperator(unsigned int _tuple);

int RetrieveAllSubscribers();

int RetrieveAllOperator();

int RetrieveAggregatedData();

int CloseEverything();

#endif /* __UI_H__ */

