setwd("~/Desktop/Capstone/Mayo/Priority Comparisons")
rm(list = ls())

## Get My Data for Oral Filled
#####Base Case
X <- read.csv("../FirstRun/data/oralFilled.txt", header = FALSE)
base <- X[,1]
#####Prof Case
X <- read.csv("../PharmVer/data/oralFilled.txt", header = FALSE)
prof <- X[,1]
#####Max Case
X <- read.csv("../Largest Queue/data/oralFilled.txt", header = FALSE)
large <- X[,1]
#####Smart Case
X <- read.csv("../VMax Priority/data/oralFilled.txt", header = FALSE)
smart <- X[,1]


treat <- rep("base", times=length(base))
df <- data.frame(base, treat)
names(df) <- c("OralThroughput", "Treatment")
anovaDat <- df
treat <- rep("prof", times=length(prof))
df <- data.frame(prof, treat)
names(df) <- c("OralThroughput", "Treatment")
anovaDat <- rbind(anovaDat,df)
treat <- rep("max", times=length(large))
df <- data.frame(large, treat)
names(df) <- c("OralThroughput", "Treatment")
anovaDat <- rbind(anovaDat,df)
treat <- rep("smart", times=length(smart))
df <- data.frame(smart, treat)
names(df) <- c("OralThroughput", "Treatment")
anovaDat <- rbind(anovaDat,df)

library(dplyr)
group_by(anovaDat, Treatment) %>%
  summarise(
    count = n(),
    mean = mean(OralThroughput, na.rm = TRUE),
    sd = sd(OralThroughput, na.rm = TRUE)
  )

library(ggplot2)
ggboxplot(my_data, x = "Treatment", y = "OralThroughput", 
          color = "Treatment", palette = c("#00AFBB", "#E7B800", "#FC4E07",  "#55FF00" ),
          order = c("base", "prof", "max", "smart"),
          ylab = "Throughput", xlab = "Treatment")
