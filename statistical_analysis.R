#load csv data
data <- read.csv("parsed_data.csv")
grouped_by_ES_list <- split(data, list(data$Engine, data$Scenario))

desired_order <-c("low", "mid", "high")
data$Scenario <- factor( as.character(data$Scenario), levels=desired_order )
data <- data[order(data$Scenario),]


#Test normality with Kolmogorov-Smirnov test
ks_energy_results <- lapply(grouped_by_ES_list, function(x){ ks.test(x$Energy, 'pnorm')})
ks_time_results <- lapply(grouped_by_ES_list, function(x){ ks.test(x$Time, 'pnorm')})

all_tests_successful <- all(sapply(append(ks_energy_results, ks_time_results), function(x) x$p.value > 0.05))

if (all_tests_successful) {
  cat("The data is normally distributed.")
} else {
  cat("The data is not normally distributed.")
}



#Test significance with a two-tailed t test
scenarios <- unique(data[,'Scenario'])

t_test_results <- list()
for (level in scenarios) {
  cpp_col <- paste0("CPP.", level)
  js_col <- paste0("JS.", level)
  
  cpp_energy <- unlist(grouped_by_ES_list[[cpp_col]]$Energy)
  js_energy <- unlist(grouped_by_ES_list[[js_col]]$Energy)
  
  cpp_time <- unlist(grouped_by_ES_list[[cpp_col]]$Time)
  js_time <- unlist(grouped_by_ES_list[[js_col]]$Time)
  
  t_test_results <- append(t_test_results, list(t.test(cpp_energy, js_energy)))
  t_test_results <- append(t_test_results, list(t.test(cpp_time, js_time)))
}

all_tests_successful <- all(sapply(t_test_results, function(x) x$p.value > 0.05))

if (all_tests_successful) {
  cat("The difference in data is significant.")
} else {
  cat("The difference in data is insignificant.")
}



#plot data
library(ggplot2)
library(dplyr)

data_sum <- data %>% group_by(Engine, Scenario) %>% 
  summarise(Energy=mean(Energy), Time=mean(Time),.groups = 'drop') %>%
  as.data.frame()

ggplot(data_sum, aes(fill=Engine, y=Time, x=Scenario)) + 
  geom_bar(position="dodge", stat="identity") +
  geom_text(aes(label = round(Time, 1)), 
            position = position_dodge(width = 0.9),
            vjust = -0.5, 
            size = 3) +
  labs(x = "Scenario", y = "Time(s)")

ggplot(data_sum, aes(fill=Engine, y=Energy, x=Scenario)) + 
  geom_bar(position="dodge", stat="identity") + 
  geom_text(aes(label = round(Energy, 2)), 
            position = position_dodge(width = 0.9),
            vjust = -0.5, 
            size = 3)+
  labs(x = "Scenario", y = "Energy(J)")