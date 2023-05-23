#load csv data
data <- read.csv("parsed_data.csv")
grouped_by_ES_list <- split(data, list(data$Engine, data$Scenario))

desired_order <-c("low", "mid", "high")
data$Scenario <- factor( as.character(data$Scenario), levels=desired_order )
data <- data[order(data$Scenario),]




#Test normality with Shapiro–Wilk test
library(plotly)
library(dplyr)

normality_test <- function(d, engine, variable) {
  split_data <- split(d, d$Engine)[[engine]][,-1]
  grouped <- split(split_data, split_data$Scenario)
  test_results <- lapply(grouped, function(x) shapiro.test(x[[variable]]))
  table <- data.frame(W = sapply(test_results, function(x) x$statistic), P = sapply(test_results, function(x) x$p.value))
  table <- table %>% mutate_if(is.numeric, round, digits=3)
  s <- unlist(lapply(row.names(table), function(x) gsub(".W", "", x)))
  plot_ly(
    type = "table",
    header = list(values = c("Scenario", "W", "P")),
    cells = list(values = rbind(s, table$W, table$P))
  ) %>% layout(title = sprintf("%s_%s", engine, variable))
}
normality_test(data, "CPP", "Energy")
normality_test(data, "JS", "Energy")
normality_test(data, "CPP", "Time")
normality_test(data, "JS", "Time")




#Test significance with a two-tailed t test
library(plotly)
library(dplyr)

significance_test <- function(d, variable, testChoice) {
  scenarios <- unique(d[,'Scenario'])
  test_results <- list()
  for (level in scenarios) {
    cpp_col <- paste0("CPP.", level)
    js_col <- paste0("JS.", level)
    
    cpp <- unlist(grouped_by_ES_list[[cpp_col]][[variable]])
    js <- unlist(grouped_by_ES_list[[js_col]][[variable]])
    test_results <- append(test_results, list(wilcox.test(cpp, js, alternative = "two.sided")))
  }
  table <- data.frame(W = sapply(test_results, function(x) x$statistic), P = sapply(test_results, function(x) x$p.value))
  #table <- table %>% mutate_if(is.numeric, round, digits=3)
  plot_ly(
    type = "table",
    header = list(values = c("W", "P")),
    cells = list(values = rbind(table$W, table$P))
  ) %>% layout(title = sprintf("JS-CPP_%s", variable))
}

# Non-normaly distributed data
significance_test(data, "Time", "wilcox")
significance_test(data, "Energy", "wilcox")
# Normally distributed data
# significance_test(data, "Time", "t")
# significance_test(data, "Energy", "t")



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
