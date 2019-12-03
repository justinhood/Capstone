setwd("~/Desktop/PSM/Fall 2019/Capstone/Mayo/Priority Comparisons")
#setwd("~/Desktop/Capstone/Mayo/Priority Comparisons")
rm(list = ls())

## Get My Data for Oral Filled
#####Max Case
X <- read.csv("../VMax Priority/Optimized/oralFilled.txt", header = FALSE)
best <- X[,1]
#####Smart Case
X <- read.csv("../VMax Priority/data/oralFilled.txt", header = FALSE)
smart <- X[,1]

treat <- rep("Best", times=length(best))
df <- data.frame(best, treat)
names(df) <- c("OralThroughput", "Treatment")
anovaDat <- df
treat <- rep("Smart", times=length(smart))
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
png("bestBox.png")
p <- ggplot(anovaDat, aes(x=Treatment, y=OralThroughput, color=Treatment)) + 
  geom_boxplot()
p + scale_color_viridis(discrete = TRUE, option="D")
dev.off()

oral.aov <- aov(OralThroughput~Treatment, data=anovaDat)
summary(oral.aov)
TukeyHSD(oral.aov)
plot(TukeyHSD(oral.aov))
png("bestCompare.png")
plot(TukeyHSD(oral.aov))
dev.off()
pairwise.t.test(anovaDat$OralThroughput, anovaDat$Treatment,
                p.adjust.method = "BH", pool.sd = FALSE)

# Extract the residuals
aov_residuals <- residuals(object = oral.aov )
# Run Shapiro-Wilk test
shapiro.test(x = aov_residuals )
