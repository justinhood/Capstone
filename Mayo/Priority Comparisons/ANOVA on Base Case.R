setwd("~/Desktop/PSM/Fall 2019/Capstone/Mayo/Priority Comparisons")
#setwd("~/Desktop/Capstone/Mayo/Priority Comparisons")
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
library(viridis)
# Basic box plot
p <- ggplot(anovaDat, aes(x=Treatment, y=OralThroughput, color=Treatment)) + 
  geom_boxplot()
p + scale_color_viridis(discrete = TRUE, option="D")

oral.aov <- aov(OralThroughput~Treatment, data=anovaDat)
summary(oral.aov)
TukeyHSD(oral.aov)
pairwise.t.test(anovaDat$OralThroughput, anovaDat$Treatment,
                p.adjust.method = "BH", pool.sd = FALSE)

# Extract the residuals
aov_residuals <- residuals(object = oral.aov )
# Run Shapiro-Wilk test
shapiro.test(x = aov_residuals )
