#setwd("~/Desktop/PSM/Fall 2019/Capstone/Mayo/Distributions")
rm(list = ls())
library(fitdistrplus)
library(logspline)
### Read Me in
X <- read.csv("Mayo_order_processing_data.csv",header = TRUE)

### Order Entry
orderEntry <- X$Order.Entry[!is.na(X$Order.Entry)]

#Histogram
hist(orderEntry) ## Looks Normal?
png("OrderEntryHist.png")
hist(orderEntry)
dev.off()

#Cullen Frey
descdist(orderEntry, discrete = FALSE) #Beta/Normal/Gamma/Lognormal/Weibull
png("OrderEntryCullen")
descdist(orderEntry, discrete = FALSE)
dev.off()

#Tests
###orderEntry.beta <- fitdist(orderEntry, "beta")
###plot(orderEntry.beta)
###orderEntry.beta$aic
##Normal AIC 219.8769
orderEntry.norm <- fitdist(orderEntry, "norm")
plot(orderEntry.norm)
gofstat(orderEntry.norm)
##Gamma AIC 221.3501
orderEntry.gamma <- fitdist(orderEntry, "gamma")
plot(orderEntry.gamma)
gofstat(orderEntry.gamma)
##LogNormal AIC 223.2712
orderEntry.log <- fitdist(orderEntry, "lnorm")
plot(orderEntry.log)
gofstat(orderEntry.log)
##Weibull 220.5979
orderEntry.w <- fitdist(orderEntry, "weibull")
plot(orderEntry.w)
gofstat(orderEntry.w)
##Beta
orderEntry.b <- fitdist(orderEntry/15, "beta")
plot(orderEntry.b)
gofstat(orderEntry.b)



### Entry Verification
orderEntryVerification <- X$Order.Entry.Verification[!is.na(X$Order.Entry.Verification)]

#Histogram
hist(orderEntryVerification)
png("EntryVerHist.png")
hist(orderEntryVerification)
dev.off()

#Cullen Frey
descdist(orderEntryVerification, discrete = FALSE) #
png("OrderEntryVerCullen")
descdist(orderEntryVerification, discrete = FALSE)
dev.off()

##Uniform
orderEntryVer.uni <- fitdist(orderEntryVerification, "unif", method="mle")
plot(orderEntryVer.uni)
gofstat(orderEntryVer.uni)
##Normal AIC 79.06169
orderEntryVer.norm <- fitdist(orderEntryVerification, "norm")
plot(orderEntryVer.norm)
gofstat(orderEntryVer.norm)
##Gamma AIC 78.97119
orderEntryVer.gamma <- fitdist(orderEntryVerification, "gamma")
plot(orderEntryVer.gamma)
gofstat(orderEntryVer.gamma)
##LogNormal AIC 79.87167
orderEntryVer.log <- fitdist(orderEntryVerification, "lnorm")
plot(orderEntryVer.log)
gofstat(orderEntryVer.log)



###Oral Prep
oralDrugPrep <- X$Oral.drug.prep[!is.na(X$Oral.drug.prep)]

#Histogram
hist(oralDrugPrep)
png("OralPrepHist.png")
hist(oralDrugPrep)
dev.off()

#Cullen Frey
descdist(oralDrugPrep, discrete = FALSE) #
png("OralPrepCullen")
descdist(oralDrugPrep, discrete = FALSE)
dev.off()

##Normal AIC 169.1392
oralDrugPrep.norm <- fitdist(oralDrugPrep, "norm")
plot(oralDrugPrep.norm)
gofstat(oralDrugPrep.norm)
##Gamma AIC 168.7099
oralDrugPrep.gamma <- fitdist(oralDrugPrep, "gamma")
plot(oralDrugPrep.gamma)
gofstat(oralDrugPrep.gamma)
##LogNormal AIC 168.5827
oralDrugPrep.log <- fitdist(oralDrugPrep, "lnorm")
plot(oralDrugPrep.log)
gofstat(oralDrugPrep.log)
##Weibull 176.7090
oralDrugPrep.w <- fitdist(oralDrugPrep, "weibull")
plot(oralDrugPrep.w)
gofstat(oralDrugPrep.w)
##Beta
oralDrugPrep.b <- fitdist(oralDrugPrep/25, "beta")
plot(oralDrugPrep.b)
gofstat(oralDrugPrep.b)



## IV drug prep
ivDrugPrep <- X$IV.drugprep[!is.na(X$IV.drugprep)]
#Histogram
hist(ivDrugPrep)
png("IVPrepHist.png")
hist(ivDrugPrep)
dev.off()

#Cullen Frey
descdist(ivDrugPrep, discrete = FALSE) #
png("IVPrepCullen")
descdist(ivDrugPrep, discrete = FALSE)
dev.off()

##Normal AIC 163.8044
ivDrugPrep.norm <- fitdist(ivDrugPrep, "norm")
plot(ivDrugPrep.norm)
gofstat(ivDrugPrep.norm)
##Gamma AIC 166.5731
ivDrugPrep.gamma <- fitdist(ivDrugPrep, "gamma")
plot(ivDrugPrep.gamma)
gofstat(ivDrugPrep.gamma)
##LogNormal AIC 173.3341
ivDrugPrep.log <- fitdist(ivDrugPrep, "lnorm")
plot(ivDrugPrep.log)
gofstat(ivDrugPrep.log)
##Weibull 163.1314
ivDrugPrep.w <- fitdist(ivDrugPrep, "weibull")
plot(ivDrugPrep.w)
gofstat(ivDrugPrep.w)


###Prep verification
orderPrepVerification <- X$Order.prep.verification[!is.na(X$Order.prep.verification)]

#Histogram
hist(orderPrepVerification)
png("prepVerification.png")
hist(orderPrepVerification)
dev.off()

#Cullen Frey
descdist(ivDrugPrep, discrete = FALSE) #
png("IVPrepCullen")
descdist(ivDrugPrep, discrete = FALSE)
dev.off()

##Normal AIC 132.4465
orderPrepVerification.norm <- fitdist(orderPrepVerification, "norm")
plot(orderPrepVerification.norm)
gofstat(orderPrepVerification.norm)
##Gamma AIC 129.8661
orderPrepVerification.gamma <- fitdist(orderPrepVerification, "gamma")
plot(orderPrepVerification.gamma)
gofstat(orderPrepVerification.gamma)
##LogNormal AIC 132.7320
orderPrepVerification.log <- fitdist(orderPrepVerification, "lnorm")
plot(orderPrepVerification.log)
gofstat(orderPrepVerification.log)
##Weibull 130.6478
orderPrepVerification.w <- fitdist(orderPrepVerification, "weibull")
plot(orderPrepVerification.w)
gofstat(orderPrepVerification.w)


dispensing <- X$Dispensing[!is.na(X$Dispensing)]
#Histogram
hist(dispensing)
png("dispensingHist.png")
hist(dispensing)
dev.off()

#Cullen Frey
descdist(dispensing, discrete = FALSE) #
png("dispensingCullen")
descdist(dispensing, discrete = FALSE)
dev.off()

##Normal AIC 80.57850
dispensing.norm <- fitdist(dispensing, "norm")
plot(dispensing.norm)
gofstat(dispensing.norm)
##Gamma AIC 80.57061
dispensing.gamma <- fitdist(dispensing, "gamma")
plot(dispensing.gamma)
gofstat(dispensing.gamma)
##LogNormal AIC 81.21407
dispensing.log <- fitdist(dispensing, "lnorm")
plot(dispensing.log)
gofstat(dispensing.log)
##Weibull 81.42169
dispensing.w <- fitdist(dispensing, "weibull")
plot(dispensing.w)
gofstat(dispensing.w)




###Oral Incoming
oralIncoming <- X$Oral.Incoming[!is.na(X$Oral.Incoming)]
#Histogram
hist(oralIncoming)
png("OralIncomingHist.png")
hist(oralIncoming)
dev.off()

#Cullen Frey
descdist(oralIncoming, discrete = FALSE) 
png("OralIncomingCullen")
descdist(oralIncoming, discrete = FALSE)
dev.off()

##Exponential AIC 306.6402
oralIncoming.exp <- fitdist(oralIncoming, "exp")
plot(oralIncoming.exp)
gofstat(oralIncoming.exp)
##Norm AIC 339.6954
oralIncoming.norm <- fitdist(oralIncoming, "norm")
plot(oralIncoming.norm)
gofstat(oralIncoming.norm)



###IV Incoming
ivIncoming <- X$IV.Incoming[!is.na(X$IV.Incoming)]
#Histogram
hist(ivIncoming)
png("IVIncomingHist.png")
hist(ivIncoming)
dev.off()

#Cullen Frey
descdist(ivIncoming, discrete = FALSE) 
png("IVIncomingCullen")
descdist(ivIncoming, discrete = FALSE)
dev.off()

##Exponential AIC 383.5409
ivIncoming.exp <- fitdist(ivIncoming, "exp")
plot(ivIncoming.exp)
gofstat(ivIncoming.exp)
